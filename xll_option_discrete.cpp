// xll_option_discrete.coo
#include <vector>
#include "xll_fi.h"
#include "fms_option_discrete.h"

#undef CATEGORY
#define CATEGORY L"OPTION"

using namespace xll;
using namespace fms;

AddIn xai_option_discrete_(
	Function(XLL_HANDLEX, L"xll_option_discrete_", L"\\" CATEGORY L".DISCRETE")
	.Arguments({
		Arg(XLL_FP, L"xi", L"is the vector of xi"),
		Arg(XLL_FP,L"p",L"is teh vector of probabilities of each xi"),
		})
		.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(L"return a handle to a discrete distribution model")
);
HANDLEX WINAPI xll_option_discrete_(_FP12* px, _FP12* pp)
{
#pragma XLLEXPORT
	HANDLEX m = INVALID_HANDLEX;

	try {
		handle<option::base<>> m_(new option::discrete::model(size(*px), px->array, pp->array));
		ensure(m_);
		m = m_.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (...) {
		XLL_ERROR(__FUNCTION__ ": unknown exception");
	}
	return m;
}

AddIn xai_option_discrete(
	Function(XLL_FP, L"xll_option_discrete", CATEGORY L".DISCRETE")
	.Arguments({
		Arg(XLL_HANDLEX, L"h", L"is a handle to an option discrete model"),
		})
	.Category(CATEGORY)
	.FunctionHelp(L"return normalized xi values")
);

_FP12* WINAPI xll_option_discrete(HANDLEX h)
{
#pragma XLLEXPORT
	static FPX x;
	try {
		handle<option::base<>> h_(h);
		ensure(h_);
		const option::discrete::model<>* pm = h_.as<option::discrete::model<>>();
		ensure(pm);
		int n = static_cast<int>(pm->xi.size());
		x.resize(n, 1);
		for (int i = 0; i < n; ++i) {
			x(i, 0) = pm->xi[i];
		}
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	catch (...) {
		XLL_ERROR(__FUNCTION__":unknown exception");
	}
	return x.get();
}