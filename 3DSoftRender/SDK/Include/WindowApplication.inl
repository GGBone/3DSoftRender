inline const char* WindowApplication::GetWindowTitle() const
{
	return mWindowTitle.c_str();
}

inline int WindowApplication::GetXPosition() const
{
	return mXPosition;
}

inline int WindowApplication::GetYPosition()const
{
	return mYPosition;
}
inline int WindowApplication::GetWidth() const
{
	return mWidth;
}

inline int WindowApplication::GetHeight()const
{
	return mHeight;
}

inline float WindowApplication::GetAspectRatio() const
{
	return (float)mWidth / (float)mHeight;
}

inline void WindowApplication::SetWindowID(int windowID)
{
	mWindowID = windowID;
}

inline int WindowApplication::GetWindowID()const
{
	return mWindowID;
}

//inline const Renderer * Hikari::WindowApplication::GetRenderer()
//{
//	return mRenderer;
//}


