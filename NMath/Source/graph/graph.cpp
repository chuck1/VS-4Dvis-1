#include <fstream>
#include <iostream>
#include <algorithm>
#include <cassert>

// gr/decl.hpp.in
#include <nmath/graph/container/edge.hpp>
#include <nmath/graph/container/vert.hpp>
#include <nmath/graph/iterator/edge_graph.hpp>
#include <nmath/graph/iterator/edge_vert.hpp>
#include <nmath/graph/pair.hpp>
#include <nmath/graph/pair_comp.hpp>
#include <nmath/graph/vert.hpp>
#include <nmath/graph/edge.hpp>
#include <nmath/graph/edge_data.hpp>

#include <nmath/graph/graph.hpp>
//
//
//
//void THIS::add_edge_util(nmath::std::shared_ptr<V> v0, nmath::std::shared_ptr<V> v1, std::shared_ptr<nmath::graph::edge_data> const & edge_data)
//{
//	auto i = iter(v0);
//	
//	(*i)->add_edge_util(v0, v1, edge_data);
//	
//	/*
//	graph::container::EDGE_S const & edges = (*i)->_M_edges;
//	
//	assert(edges);
//
//	graph::edge edge(v0, v1, edge_data);
//
//	edges->insert(edge);
//	*/
//}
//void				THIS::add_edge(nmath::std::shared_ptr<V> v0, nmath::std::shared_ptr<V> v1)
//{
//	auto data = std::make_shared<nmath::graph::edge_data>();
//	
//	add_edge_util(v0, v1, data);
//	add_edge_util(v1, v0, data);
//}
//nmath::graph::iterator::vert_graph	THIS::iter(nmath::std::shared_ptr<V> v)
//{
//	auto it = vert_find(v);
//
//	if(it == vert_end()) {
//		
//		CONT_VERT::value_type p(v);
//
//		return graph::iterator::vert_graph(_M_verts, _M_verts.insert(_M_verts.begin(), p));
//	}
//
//	return it;
//}
//
//
//
//nmath::graph::iterator::vert_graph		THIS::vert_begin()
//{
//	return graph::iterator::vert_graph(_M_verts, _M_verts.begin());
//}
//nmath::graph::iterator::vert_graph		THIS::vert_end()
//{
//	return graph::iterator::vert_graph(_M_verts, _M_verts.end());
//}
//nmath::graph::iterator::vert_graph_all		THIS::vert_begin_all()
//{
//	return graph::iterator::vert_graph_all(_M_verts, _M_verts.begin());
//}
//nmath::graph::iterator::vert_graph_all		THIS::vert_end_all()
//{
//	return graph::iterator::vert_graph_all(_M_verts, _M_verts.end());
//}
//nmath::graph::iterator::vert_graph_all		THIS::vert_begin_all(nmath::graph::VERT_FUNC func)
//{
//	return graph::iterator::vert_graph_all(_M_verts, _M_verts.begin(), func);
//}
//nmath::graph::iterator::vert_graph_all		THIS::vert_end_all(nmath::graph::VERT_FUNC func)
//{
//	return graph::iterator::vert_graph_all(_M_verts, _M_verts.end(), func);
//}
//
//
//
//
//nmath::graph::iterator::vert_graph		THIS::vert_erase(nmath::graph::iterator::vert_graph & i)
//{
//	graph::VERT_W w = *i;
//	assert(!w.expired());
//
//	auto ret = _M_verts.erase(i._M_j);
//
//	assert(w.expired());
//
//	edge_erase();
//
//	return graph::iterator::vert_graph(_M_verts, ret);
//}
//nmath::graph::iterator::vert_graph		THIS::vert_find(nmath::std::shared_ptr<V> v)
//{
//	return graph::iterator::vert_graph(_M_verts, _M_verts.find(v));
//}
//
//void					THIS::edge_erase()
//{
//	//std::cout << "edge erase" << std::endl;
//	for(auto j = vert_begin(); j != vert_end(); ++j) {
//		assert(*j);
//		(*j)->edge_erase_disconnected();
//	}
//}
//nmath::graph::iterator::edge_graph		THIS::edge_begin()
//{
//	return graph::iterator::edge_graph(_M_verts, _M_verts.begin());
//}
//nmath::graph::iterator::edge_graph	THIS::edge_end()
//{
//	return graph::iterator::edge_graph(_M_verts, _M_verts.end());
//}
//
//
//
//
//
//
//nmath::graph::iterator::vert_comp		THIS::comp_vert_begin(int c)
//{
//	return graph::iterator::vert_comp(_M_verts, _M_verts.begin(), c);
//}
//nmath::graph::iterator::vert_comp		THIS::comp_vert_end(int c)
//{
//	return graph::iterator::vert_comp(_M_verts, _M_verts.end(), c);
//}
//
//
//
//
//
//
//void THIS::edge_erase_util(nmath::std::shared_ptr<V> & v0, nmath::std::shared_ptr<V> & v1)
//{
//	auto i = vert_find(v0);
//
//	if(i == vert_end()) throw std::exception();
//
//	(*i)->edge_erase_util(v0, v1);
//
//	/*
//	graph::container::EDGE_S const & edges = (*i)->_M_edges;
//
//	auto j = edges->find(v1);
//	//auto j = std::find(edges.begin(), edges.end(), v1);
//
//	if(j == edges->end()) throw std::exception();
//
//	edges->erase(j);
//	*/
//	//for(auto j = edges.begin(); j != edges.end(); ++j) {
//	//	std::shared_ptr<V> w = j->first.lock();
//	//}
//}
//void				THIS::edge_erase(nmath::std::shared_ptr<V> & v0, nmath::std::shared_ptr<V> & v1)
//{
//	edge_erase_util(v0, v1);
//	edge_erase_util(v1, v0);
//}
//nmath::graph::iterator::edge_graph	THIS::edge_erase(nmath::graph::iterator::edge_graph i)
//{
//	nmath::graph::iterator::edge_graph ret(i);
//
//	nmath::graph::container::edge & container = *((*i._M_i)->_M_edges);
//
//	ret._M_j = container.erase(i._M_j);
//
//	ret.next();
//
//	return ret;
//}
//
//
///*
//   graph::VEC_Edge		THIS::get_edges(int c)
//   {
//   graph::VEC_Edge ret;
//   auto l = [=](graph::EDGE_S e) {
//   return e->n0()->comp._M_c == c;
//   };
//   std::copy_if(_M_edges.begin(), _M_edges.end(), std::back_inserter(ret), l);
//   return ret;
//   }
//   graph::VEC_Edge		THIS::get_edges()
//   {
//   return _M_edges;
//   }
//   graph::SET_Node		THIS::get_nodes()
//   {
//   SET_Node ret;
//
//   for(auto e : _M_edges) {
//   e->n0()->_M_graph = shared_from_this();
//   e->n1()->_M_graph = shared_from_this();
//   ret.insert(e->n0());
//   ret.insert(e->n1());
//   }
//
//   return ret;
//   }
//   graph::SET_Node		THIS::get_nodes(int c)
//   {
//   SET_Node ret;
//
//   for(auto e : _M_edges) {
//   if(e->n0()->comp._M_c != c) continue;
//
//   e->n0()->_M_graph = shared_from_this();
//   e->n1()->_M_graph = shared_from_this();
//   ret.insert(e->n0());
//   ret.insert(e->n1());
//   }
//
//   return ret;
//   }
//   */
//void				THIS::distance_util(nmath::std::shared_ptr<V> u)
//{
//	//v->dist._M_visited = true;
//
//	int d = u->dist._M_distance + 1.0f;
//
//	for(auto it = u->edge_begin(); it != u->edge_end();) {
//		std::shared_ptr<V> const & v = it->_M_v1.lock();
//
//		if(!v) {
//			//throw std::exception();
//			it = u->edge_erase(it);
//		} else {
//
//			if((v->dist._M_distance < 0) || (v->dist._M_distance > d)) {
//				v->dist._M_distance = d;
//
//				// ???
//				distance_util(v);
//			}
//
//			++it;
//		}
//	}
//}
//void				THIS::distance(nmath::std::shared_ptr<V> const & v0)
//{
//	//auto unvisited = get_nodes();
//	for(auto it = vert_begin(); it != vert_end(); ++it)
//	{
//		//it->first->dist._M_visited = false;
//		(*it)->dist._M_distance = -1.0;
//	}
//
//	//SET_Node s;
//
//	//auto it = unvisited.find(n0);
//	auto it = vert_find(v0);
//
//	if(it == vert_end()) {
//		std::cout << "graph::distance v0 not found" << std::endl;
//		throw std::exception();
//	}
//
//	//s.insert(*it);
//	//unvisited.erase(it);
//	//it = s.begin();
//
//	std::shared_ptr<V> const & v = *it;
//
//	v->dist._M_distance = 0.0;
//
//	distance_util(v);
//
//	/*
//	   while(true) {
//	   auto nodes = (*it)->get_adjacent_nodes();
//
//	// visit each
//	for(auto n : nodes) {
//	auto it1 = unvisited.find(n);
//	if(it1 != unvisited.end()) {
//
//	double d = (*it)->_M_distance + 1.0;
//
//	if(((*it1)->_M_distance == -1.0) || ((*it1)->_M_distance > d)) {
//	(*it1)->_M_distance = d;
//	}
//
//	s.insert(*it1);
//	unvisited.erase(it1);
//
//	}
//	}
//
//	// remove current node from set s
//	s.erase(it);
//	// choose new focus node
//	it = s.begin();
//
//	if(it == s.end()) break;
//	}
//	*/
//}
//void				THIS::vert_erase_layer(unsigned int l)
//{
//	if(l > _M_layers.size()) throw std::exception();
//
//	auto const & layer = _M_layers[l];
//
//	for(auto i = vert_begin(); i != vert_end();) {
//
//		if(!(*i)->_M_layer.expired()) {
//			if((*i)->_M_layer.lock() == layer) {
//				i = vert_erase(i);
//				continue;
//			}
//		}
//
//		++i;
//	}
//}
//void				THIS::bridges_sub(nmath::std::shared_ptr<V> const & n, int & t, std::vector<nmath::graph::edge> & ret)
//{
//	n->bridge._M_visited = true;
//
//	n->bridge._M_disc = n->bridge._M_low = ++t;
//
//	for(auto i = n->edge_begin(); i != n->edge_end(); ++i) {
//		nmath::std::shared_ptr<V> const & v = i->_M_v1.lock();
//
//		assert(v);
//
//		if(!v->bridge._M_visited) {
//			v->bridge._M_parent = n;
//
//			bridges_sub(v, t, ret);
//
//			n->bridge._M_low = std::min(n->bridge._M_low, v->bridge._M_low);
//
//			if(v->bridge._M_low > n->bridge._M_disc) {
//				ret.push_back(*i);
//			}
//		} else if(v != n->bridge._M_parent.lock()) {
//			n->bridge._M_low = std::min(n->bridge._M_low, v->bridge._M_disc);
//		}
//	}
//}
//std::vector<nmath::graph::edge>		THIS::bridges()
//{
//	std::vector<nmath::graph::edge> ret;
//
//	int t = 0;
//
//	// initialize
//	for(auto i = _M_verts.begin(); i != _M_verts.end(); ++i) {
//		(*i)->bridge._M_visited = false;
//	}
//
//	for(auto i = _M_verts.begin(); i != _M_verts.end(); ++i) {
//		if((*i)->bridge._M_visited == false) {
//			bridges_sub(*i, t, ret);
//		}
//	}
//
//	return ret;
//}
//void				THIS::dot()
//{
//	std::ofstream of;
//	of.open("graph.dot");
//
//	of << "graph {" << std::endl;
//
//	for(auto i = edge_begin(); i != edge_end(); ++i) {
//		of << "node" << i->_M_v0.lock().get() << " -- node" << i->_M_v1.lock().get() << std::endl;
//	}
//
//	for(auto i = vert_begin(); i != vert_end(); ++i) {
//		//of << "node" << n.get() << " [" << "]"
//	}
//
//	of << "}" << std::endl;
//}
//void				THIS::components_util(nmath::std::shared_ptr<V> const & u, int c)
//{
//	assert(u);
//
//	u->comp._M_visited = true;
//	u->comp._M_c = c;
//	
//	auto i0 = u->edge_begin();
//	auto i1 = u->edge_end();
//
//	for(auto i = i0; i != i1; ++i) {
//
//		unsigned int d = std::distance(i, i1);
//		assert(d!=0);
//
//		nmath::std::shared_ptr<V> const & v = i->_M_v1.lock();
//
//		assert(u == i->_M_v0.lock());
//		assert(v != u);
//
//		if(!v) throw std::exception();
//
//		if(!(v->comp._M_visited)) {
//			components_util(v, c);
//		}
//	}
//}
//int					THIS::components()
//{
//	edge_erase();
//
//	// initialize
//	for(auto i = vert_begin(); i != vert_end(); ++i) {
//		(*i)->comp._M_visited = false;
//		(*i)->comp._M_c = -1;
//	}
//
//	int c = 0;
//
//	for(auto i = vert_begin(); i != vert_end(); ++i) {
//		std::shared_ptr<V> const & u = *i;
//
//		assert(u);
//
//		if(!(u->comp._M_visited)) {
//			components_util(u, c);
//			++c;
//		}
//	}
//
//	if(0) {
//		std::cout << "verts" << std::endl;
//		for(auto i = vert_begin(); i != vert_end(); ++i) {
//			std::cout << "  " << (*i)->comp._M_c << " " << (*i)->comp._M_c << std::endl;
//		}
//		std::cout << "comps" << std::endl;
//		for(int i = 0; i < c; ++i) {
//			auto s = std::distance(comp_vert_begin(i), comp_vert_end(i));
//			std::cout << "  " << i << " " << s << std::endl;
//		}
//	}
//	return c;
//}
//void				THIS::component(int c)
//{
//	for(auto it = vert_begin(); it != vert_end();) {
//
//		std::shared_ptr<V> const & u = *it;
//
//		assert(u);
//
//		if(u->comp._M_c == c) {
//			++it;
//		} else {
//			it = vert_erase(it);
//		}
//	}
//}
//void				THIS::edge_enable()
//{
//	edge_erase();
//
//	for(auto i = edge_begin(); i != edge_end(); ++i) {
//		auto const & data = i->_M_data;
//		assert(data);
//		data->_M_enabled = true;
//	}
//}
//void				THIS::vert_enable()
//{
//	for(auto i = vert_begin(); i != vert_end(); ++i) {
//		(*i)->_M_enabled = true;
//	}
//}
//void				THIS::layer_move(unsigned int i0, unsigned int i1)
//{
//	// move all verts in i0 to i1
//	
//	if(i0 < _M_layers.size()) throw std::exception();
//	if(i1 < _M_layers.size()) throw std::exception();
//
//	auto const & l0 = _M_layers[i0];
//	auto const & l1 = _M_layers[i1];
//	
//	assert(l0);
//	assert(l1);
//	
//	for(auto i = vert_begin_all(); i != vert_end_all(); ++i) {
//		auto const & u = *i;
//
//		if(!u->_M_layer.expired()) {
//			if(u->_M_layer.lock() == l0) {
//				u->_M_layer = l1;
//			}
//		}
//	}
//}
//unsigned int		THIS::vert_size()
//{
//	//auto s1 = _M_verts.size();
//	auto s2 = std::distance(vert_begin(), vert_end());
//	//assert(s1 == s2);
//	return s2;
//}
//
//
//
