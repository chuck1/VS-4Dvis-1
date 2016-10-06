#ifndef NMATH_GEOMETRY_POLYTOPE
#define NMATH_GEOMETRY_POLYTOPE


#include <memory>

#include <nmath/util/Array.h>
#include <nmath/geometry/GraphTopology.h>
#include <nmath/geometry/Plane.h>
#include <nmath/geometry/Ray.h>

namespace nmath {
	namespace geometry {

		template<unsigned int M>
		class VoronoiRegionBoundary
		{
			typedef std::shared_ptr<nmath::util::ArrayRefIndexRef<nmath::geometry::Plane<M>>> PLANE;

			PLANE			_M_plane;
			unsigned int	_M_plane_ref;
			char			_M_sign;
		};
		
		template<unsigned int M>
		class VoronoiRegion
		{
		public:
			std::vector<VoronoiRegionBoundary<M>>		_M_boundaries;
		};

		template<unsigned int K>
		class Inequality
		{
		public:
			Inequality(){}
			Inequality(nmath::linalg::Vec<K> const & a, double d):
				_M_a(a),
				_M_d(d)
			{}

			double d(nmath::linalg::Vec<K> const & s)
			{
				return nmath::linalg::dot(_M_a, s);
			}
			bool eval(nmath::linalg::Vec<K> const & s)
			{
				return (d(s) < _M_d);
			}

			nmath::linalg::Vec<K> _M_a;
			double _M_d;
		};

		template<unsigned int M, unsigned int K>
		class Subspace
		{
		public:
			nmath::linalg::Vec<K> s(nmath::linalg::Vec<M> x)
			{
				return _M_A.transpose()*(x - _M_p);
			}

			/* parameterization */
			nmath::Mat<M, K> _M_A;
			nmath::linalg::Vec<M> _M_p;
		};

		template<unsigned int M, unsigned int K>
		class SubspaceBounded: public Subspace<M,K>
		{
		public:
			/**
			* Add the intersection of this subspace and hyperplane p to the list of inequalities.
			* So add p as a boundary of the subspace.
			*/
			void AddHyperplaneIntersection(nmath::geometry::Plane<M> const & p)
			{
				auto a = _M_A.transpose() * p.n;
				double d = p.d - nmath::linalg::dot(p.n, _M_p);
				_M_inequalities.push_back(Inequality<K>(a, d));
			}

			std::vector<Inequality<K>> _M_inequalities;
		};

		template<unsigned int M>
		class Face : public SubspaceBounded<M, M-1>
		{
		public:
			//typedef std::shared_ptr<nmath::util::ArrayRef<nmath::geometry::Plane<M>>> PLANE;
			//PLANE _M_plane;

			void calc_basis()
			{
				nmath::Mat<M, 1> m;
				for (int i = 0; i < M; ++i) m(i, 0) = _M_plane.n(i);

				auto m2 = nmath::SMat<M>::Identity();

				nmath::gaussianElimination(m, m2);

				_M_A = nmath::subMat1(m2.transpose(), 0);
			}
			bool intersection(nmath::geometry::Ray<M> ray, double & k)
			{
				double k1 = (_M_plane.d - nmath::linalg::dot(_M_plane.n, ray.p)) / nmath::linalg::dot(_M_plane.n, ray.v);

				if (k1 > k) return false;

				// test boundaries
				auto x = ray.x(k1);
				auto s1 = s(x);

				for (unsigned int i = 0; i < _M_inequalities._M_size; ++i)
				{
					if (!_M_inequalities[i].eval(s1)) return false;;
				}

				// passed
				k = k1;
				return true;
			}
		public:
			nmath::geometry::Plane<M> _M_plane;
		};

		template<unsigned int M>
		class PolytopePrimitive
		{
		public:
			std::vector<VoronoiRegion<M>>	_M_voronoi_regions;
			std::vector<unsigned int>		_M_planes_ref;
		};

		template<unsigned int M>
		class Polytope: public PolytopePrimitive<M>, public FeatureSet<M, M-1>
		{
		public:
			//typedef std::shared_ptr<nmath::util::ArrayRefIndexRef<nmath::geometry::Plane<M>>> PLANE;
			//PLANE _M_planes[NMATH_GEOMETRY_POLYTOPE_MAX_PLANES];

			Face<M> _M_faces[16];
			
			/** graph
			*/
			std::shared_ptr<nmath::geometry::topo::Graph<M>> _M_topology;
		};
	}
}

#endif


