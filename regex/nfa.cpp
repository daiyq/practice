#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "nfa.h"
//#include <cassert>

DirectedGraph::DirectedGraph(size_t n) :p(n), e(n), marked(n) {

}

char DirectedGraph::ichar(size_t v) {
	return p[v].ch;
}
void DirectedGraph::add_point(const Vertex& vertex) {
	p.push_back(vertex);
}

void DirectedGraph::add_edge(size_t i, size_t j) {
	//assert(i >= 0 && j >= 0);
	e[i].insert(j);
}

size_t DirectedGraph::num_vertex() const {
	return p.size();
}

void DirectedGraph::dfs(size_t v) {
	//assert(v >= 0);
	for (size_t i = 0; i < num_vertex(); i++) {
		marked.push_back(false);
	}
	for (auto i : e[v]) {
			dfs_(i);
	}
}

void DirectedGraph::dfs(const std::set<size_t>& vs) {
	for (size_t i = 0; i < num_vertex(); i++) {
		marked.push_back(false);
	}
	for (auto i : vs) {
		dfs(i);
	}
}

void DirectedGraph::dfs_(size_t v) {
	//assert(v >= 0);
	marked[v] = true;
	for (auto i : e[v]) {
		if (!marked[i])
			dfs_(i);
	}
}

bool DirectedGraph::is_mark(size_t v) {
	return marked[v];
}

NFA::NFA(std::string regex) :g(regex.size() + 1), match_to(regex.size()) {
	next(regex);
	Vertex v;
	for (size_t i = 0; i < regex.size(); i++) {
		v.ch = regex[i];
		g.add_point(v);
	}

	for (size_t i = 0; i < regex.size(); i++) {
		size_t lp = i;
		//parse '(', ')', '|'
		if (regex[i] == '(' || regex[i] == '|')
			s.push(i);
		if (regex[i] == ')') {
			std::stack<size_t> vertical;
			size_t or = s.top();
			s.pop();
			//milti '|'
			while (regex[or ] == '|') {
				vertical.push(or );
				size_t or = s.top();
				s.pop();
			}
			lp = or ;
			while (vertical.size() != 0) {
				or = vertical.top();
				vertical.pop();
				g.add_edge(lp, or +1);
				g.add_edge(or, i);
			}	
			/*
			if (regex[or] == '|') {
				lp = s.top();
				s.pop();
				if (regex[lp] == '(') {
					g.add_edge(lp, or +1);
					g.add_edge(or , i);
				}
				
			}
			else
				//regex[lh]=='(' need to be tested
				lp = or ;
			*/
		}
		//parse '[', ']'	
		if (regex[i] == '[')
			s.push(i);
		if (regex[i] == ']') {

			size_t or = s.top();
			s.pop();
			lp = or ;
			for (size_t j = or + 1; j < i; j++) {
				g.add_edge(or, j);
			}
		}
		//parse '*', '+', '?'
		if (i < regex.size() - 1) {
			if (regex[i + 1] == '*') {
				g.add_edge(lp, i + 1);
				g.add_edge(i + 1, lp);
			}
			if (regex[i + 1] == '+') {
				g.add_edge(i + 1, lp);
			}
			if (regex[i + 1] == '?') {
				g.add_edge(lp, i + 1);
			}
		}

		if (regex[i] == '(' || regex[i] == ')' || regex[i] == '*' || regex[i] == '+' || regex[i] == '?' || regex[i] == ']')
			g.add_edge(i, i + 1);
	}
	g.add_edge(regex.size() - 1, regex.size());
}

bool NFA::recognize(std::string text) {
	g.dfs(0);
	std::set<size_t> status;
	for (size_t i = 0; i < g.num_vertex(); i++) {
		if (g.is_mark(i))
			status.insert(i);
	}
	for (size_t i = 0; i < text.size(); i++) {
		std::set<size_t> match;
		for (auto it : status) {
			if (it < g.num_vertex()) {
				if (g.ichar(it) == text[it] || g.ichar(it) == '.')
					match.insert(match_to[it]);
			}
		}
		status.clear();
		g.dfs(match);
		for (size_t j = 0; j < g.num_vertex(); j++) {
			if (g.is_mark(j))
				status.insert(j);
		}
	}
	for (auto i : status) {
		if (i == g.num_vertex())
			return true;
	}
	return false;
}

void NFA::next(const std::string& regex) {
	std::stack<char> c;
	for (size_t i = 0; i < regex.size(); i++) {
		if (regex[i] == '[')
			c.push(regex[i]);
		//inside "[]" is a-z, A-Z, 0-9
		if (regex[i] == ']') {
			size_t j = i;
			while (c.top() != '[') {
				j--;
				match_to[j] = i;
				c.pop();
			}
			c.pop();
		}
	}
}