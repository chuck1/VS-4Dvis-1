#include <iostream>
#include <algorithm>
#include <cassert>

#include <nmath/graph/container/edge.hpp>
#include <nmath/graph/iterator/edge_vert.hpp>
#include <nmath/graph/pair.hpp>
#include <nmath/graph/edge.hpp>
#include <nmath/graph/graph.hpp>
#include <nmath/graph/layer.hpp>
#include <nmath/graph/vert.hpp>
//
//typedef nmath::graph::vert THIS;
//
//THIS::vert(nmath::graph::GRAPH_S g) :
//	_M_enabled(true),
//	_M_graph(g),
//	_M_edges(new nmath::graph::container::edge)
//{
//}
//THIS::~vert()
//{
////	std::cout << "vert destroyed" << std::endl;
//}
//bool				THIS::enabled() const
//{
//	if(!_M_enabled) return false;
//
//	if(!_M_layer.expired()) {
//		if(!_M_layer.lock()->_M_enabled) return false;
//	}
//
//	return true;
//}
//nmath::graph::GRAPH_S			THIS::get_graph()
//{
//	auto ret = _M_graph.lock();
//	assert(ret);
//	return ret;
//}
//nmath::graph::iterator::edge_vert		THIS::edge_begin()
//{
//	return nmath::graph::iterator::edge_vert(*_M_edges, _M_edges->begin());
//}
//nmath::graph::iterator::edge_vert		THIS::edge_end()
//{
//	return nmath::graph::iterator::edge_vert(*_M_edges, _M_edges->end());
//}
//nmath::graph::iterator::edge_vert		THIS::edge_erase(nmath::graph::iterator::edge_vert & i)
//{
//	auto j = _M_edges->erase(i._M_i);
//
//	return nmath::graph::iterator::edge_vert(*_M_edges, j);
//}
//
//void				THIS::edge_erase_disconnected()
//{
//	for(auto i = edge_begin(); i != edge_end();) {
//
//		if(i->_M_v0.expired()) throw std::exception();
//
//		if(i->_M_v1.expired()) {
//			//std::cout << "graph::vert erase edge" << std::endl;
//			i = edge_erase(i);
//		} else {
//			++i;
//		}
//	}
//}
//unsigned int			THIS::edge_size()
//{
//	return std::distance(edge_begin(), edge_end());
//}
//void				THIS::add_edge_util(
//	nmath::graph::VERT_S v0,
//	nmath::graph::VERT_S v1,
//	std::shared_ptr<nmath::graph::edge_data> const & edge_data)
//{
//	assert(_M_edges);
//
//	nmath::graph::edge edge(v0, v1, edge_data);
//
//	_M_edges->insert(edge);
//}
//void				THIS::edge_erase_util(nmath::graph::VERT_S & v0, nmath::graph::VERT_S & v1)
//{
//	//graph::container::EDGE_S const & edges = (*i)->_M_edges;
//
//	auto j = _M_edges->find(v1);
//	//auto j = std::find(edges.begin(), edges.end(), v1);
//
//	if(j == _M_edges->end()) throw std::exception();
//
//	_M_edges->erase(j);
//
//	//for(auto j = edges.begin(); j != edges.end(); ++j) {
//	//	graph::VERT_S w = j->first.lock();
//	//}
//}
//
//
//
