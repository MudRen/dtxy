/*
	www/cgi-bin/inc_footer.c
	Created by Ammy@YSZZ
	2001/04/13
	在每个页面的底部调用
	modified by emotion
*/
inherit F_CLEAN_UP;
#include <mudlib.h>
string gateway()
{
	return MUDLIB_NAME;
}