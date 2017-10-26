/*
update:2017/10/25
supported:alternation, concatenation('|'), the repetition operators('*') 
		  and parentheses('(',')')
		  1.1, 1.2, 2.1, 2.2 below
///
use NFA(Nondeterministic Finite Automata) to support regex parseing
reference website:https://swtch.com/~rsc/regexp/
https://algs4.cs.princeton.edu/54regexp/
key points:1.NFA	2.DirectedGraph
do not support unicode or back reference.

support alternation, concatenation('|'), the repetition operators('*').
Explicit parentheses can be used to force different meanings.
and abbreviated writing has 3 types:
1.Character set descriptor
	1.1	Wildcard.	eg:	A.B
	1.2	specified collection[]	eg:	[ASD]	which means character is A	or S or D
	1.3	range collection[-]		eg:	[A-D][0-9]	similar
	1.4	complement[^]		eg:[^USDF]	which is not U, not S, not D, not F
2.closure for short
	2.1	+:at least once		eg:(AB)+   which can be writen like (AB)(AB)*
	2.2	?:zero or once		eg:(AB)?   which can be writen like AB | empty string
	2.3	{number}:specified times			eg:(AB){3}		which is equal to ABABAB
	2.4	{number-number}:range of times		eg:(AB){1-2}	which can be writen like AB | ABAB
3.Transfer sequence
	the metacharacters .*+?()| are used to build regex.
	To match a metacharacter itself, escape it with a backslash: \ plus character.
	eg: '\.' means '.' itself.
*/

#ifndef NFA_H_
#define NFA_H_
#include <vector>
#include <set>
#include <string>
#include <stack>

struct Vertex {
	char ch;
};

class DirectedGraph {
private:
	std::vector<Vertex> p;
	std::vector<std::set<size_t>> e; //edge
	std::vector<bool> marked;
public:
	DirectedGraph(size_t n);
	char ichar(size_t v);
	void add_point(const Vertex& vertex);
	void add_edge(size_t i, size_t j);
	size_t num_vertex() const;
	void dfs(size_t v);
	void dfs(const std::set<size_t>& vs);
	bool is_mark(size_t v);
private:
	void dfs_(size_t v);
};

class NFA{
public:
	NFA(std::string regex);
	NFA(const NFA& nfa) = delete;
	NFA& operator=(const NFA& NFA) = delete;
	bool recognize(std::string text); //parse text

private:
	void next(const std::string& regex);

private:
	DirectedGraph g;
	std::stack<size_t> s;
	std::vector<size_t> match_to;
};

#endif