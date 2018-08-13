#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std;


class Solution0736 {
public:
	int evaluate(string expression) {
		const char* ps = expression.c_str();
		vector<unordered_map<string, int>> st;
		return dispatch(ps, st);
	}

private:
	int dispatch(const char* &ps, vector<unordered_map<string, int>>& st) const
	{
		string word;
		ps = next(ps, word);

		if (word == "(")
		{
			ps = next(ps, word);
			if (word == "let")
				return eval_let(ps, st);
			if (word == "add")
				return eval_op(ps, st, '+');
			if (word == "mult")
				return eval_op(ps, st, '*');
		}

		return eval_var(word, st);
	}

	int eval_let(const char* &ps, vector<unordered_map<string, int>>& st) const
	{
		{
			unordered_map<string, int> v;
			st.push_back(v);
		}
		auto& vars = st.back();

		int val = 0;
		string word1, word2;
		do
		{
			ps = next(ps, word1);
			if (word1 == "(")
			{
				--ps;
				val = dispatch(ps, st);
				ps = next(ps, word2);		// end of let
				assert(word2 == ")");
				break;
			}
			ps = next(ps, word2);
			if (word2 == ")")
			{
				val = eval_var(word1, st);
				break;
			}

			int e;
			if (word2 == "(")
			{
				--ps;
				e = dispatch(ps, st);
			}
			else
				e = eval_var(word2, st);

			auto iter = vars.find(word1);
			if (iter != vars.end())
				vars.erase(iter);
			vars.emplace(word1, e);
		} while (*ps);

		st.pop_back();
		return val;
	}

	int eval_op(const char* &ps, vector<unordered_map<string, int>>& st, int opr) const
	{
		int e1 = 0, e2 = 0;
		string word;

		ps = next(ps, word);
		if (word == "(")
		{
			--ps;
			e1 = dispatch(ps, st);
		}
		else
			e1 = eval_var(word, st);

		ps = next(ps, word);
		if (word == "(")
		{
			--ps;
			e2 = dispatch(ps, st);
		}
		else
			e2 = eval_var(word, st);

		ps = next(ps, word);
		assert(word == ")");

		switch (opr)
		{
		case '*':
			return e1 * e2;
		}

		return e1 + e2;
	}

	int eval_var(const string& s, const vector<unordered_map<string, int>>& st) const
	{
		int nn = (int)st.size();
		while (nn-- > 0)
		{
			auto iter = st[nn].find(s);
			if (iter != st[nn].end())
			{
				return iter->second;
			}
		}
		return ::atoi(s.c_str());
	}

	const char* next(const char* ps, string& word) const
	{
		if (*ps == '(')
		{
			word = "(";
			++ps;
		}
		else if (*ps == ')')
		{
			word = ")";
			++ps;
		}
		else
		{
			int n = 0;
			while (ps[n])
			{
				if (ps[n] == '(' || ps[n] == ')' || ps[n] == ' ')
					break;
				++n;
			}
			word.assign(ps, ps + n);
			ps += n;
		}

		while (*ps == ' ')
			++ps;
		return ps;
	}
};


void test0736_evaluate()
{
	int nn;
	Solution0736 sol;

	nn = sol.evaluate("(add 1 2)");
	assert(nn == 3);

	nn = sol.evaluate("(mult 3 (add 2 3))");
	assert(nn == 15);

	nn = sol.evaluate("(let x 2 (mult x 5))");
	assert(nn == 10);

	nn = sol.evaluate("(let x 2 (mult x (let x 3 y 4 (add x y))))");
	assert(nn == 14);

	nn = sol.evaluate("(let x 3 x 2 x)");
	assert(nn == 2);

	nn = sol.evaluate("(let x 1 y 2 x (add x y) (add x y))");
	assert(nn == 5);

	nn = sol.evaluate("(let x 2 (add (let x 3 (let x 4 x)) x))");
	assert(nn == 6);

	nn = sol.evaluate("(let a1 3 b2 (add a1 1) b2)");
	assert(nn == 4);

	nn = sol.evaluate("(let var 78 b 77 (let c 33 (add c (mult var 66))))");
	assert(nn == 5181);

	
}