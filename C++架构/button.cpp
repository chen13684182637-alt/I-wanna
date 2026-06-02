#include"button.h"

const wchar_t* ConstCharToLPCTSTR1(const char* cstr, UINT codePage ){
	if (cstr == nullptr) return nullptr;

	// 1. 计算宽字符所需长度
	int wideLen = MultiByteToWideChar(codePage, 0, cstr, -1, nullptr, 0);
	if (wideLen == 0) return nullptr; // 转换失败

	// 2. 动态分配宽字符缓冲区（用 malloc 方便后续 free）
	wchar_t* wstr = (wchar_t*)malloc(wideLen * sizeof(wchar_t));
	if (wstr == nullptr) return nullptr;

	// 3. 执行转换
	MultiByteToWideChar(codePage, 0, cstr, -1, wstr, wideLen);
	return wstr;
}