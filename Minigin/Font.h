#pragma once
#include "Component.h"

struct _TTF_Font;
namespace dae
{
	/**
	 * Simple RAII wrapper for an _TTF_Font
	 */
	class Font : public BaseComponent
	{
	public:
		_TTF_Font* GetFont() const;
		explicit Font(const std::string& fullPath, unsigned int pixalheight);
		~Font();

		void Update(float DeltaTime) override { DeltaTime; };
		void Render()const override {};

		Font(const Font &) = delete;
		Font(Font &&) = delete;
		Font& operator= (const Font& other) = delete;
		Font & operator= (const Font && other) = delete;
	private:
		_TTF_Font* m_Font;
		unsigned int m_Size;
	};
}
