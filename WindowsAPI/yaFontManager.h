#pragma once
#include "Common.h"

namespace ya
{
	class FontManager
	{

	public:
		FontManager();
		~FontManager();

		void LoadFont();

		void WriteCounterText(HDC hdc, int posX, int posY, std::wstring _szMessage);
		void WriteNameText(HDC hdc, int posX, int posY, int width, int height, std::wstring _szMessage);
		void WriteScriptText(HDC hdc, int posX, int posY, int width, int height, std::wstring _szMessage);

		void Exit();

	private:
		HFONT mCounterFont;
		HFONT mNameFont;
		HFONT mScriptFont;
	};

}

