/*
	www/cgi-bin/inc_header.c
	Created by Ammy@YSZZ
	2001/04/13
	在每个页面的顶部调用
	modified by emotion

	emotion note: We don't demonstrate good coding style here is to conserve network resource!!
*/

#include <mudlib.h>

string report()
{
        int t, d, h, m, s;
        string time;

        t = uptime();
        s = t % 60;             t /= 60;
        m = t % 60;             t /= 60;
        h = t % 24;             t /= 24;
        d = t;

        if(d) time = chinese_number(d) + "天";
        else time = "";

        if(h) time += chinese_number(h) + "小时";
        if(m) time += chinese_number(m) + "分";
        time += chinese_number(s) + "秒\n";
        return time;
}

string gateway()
{
        string ret;

        ret="<head><title>"+MUDLIB_NAME+"在线查询</title>\n<meta http-equiv='content-type' content='text/html; charset=gb2312'></head>\n\n";
        ret+="<table align='center' border='0' cellPadding='0' cellSpacing='0'width='100%'>\n<td align='center' valign='top' width='50%'>\n<table border='0' cellPadding='2' cellSpacing='0'>\n";
        ret+="<tr><td align='center'><font face='宋体' style='font-size:16pt'><b><a href='http://ywxrzrdtxy.jumbocool.com/'>返回 "
             + MUDLIB_NAME+ "主页</a></b></font></td></tr>\n";
        ret+="<tr><td>&nbsp;</td></tr><tr><td align='center'><b>"+MUDLIB_NAME
             +"实时在线查询</b></td></tr><tr><td align='center'>当前本游戏已经不间断运行了 " + report()
             + "</td></tr><tr><td>&nbsp;</td></tr><tr><td align='center'><a href='board_list.c'>留言板</a> | <a href='wizlist.c'>巫师列表</a> | <a href='who.c'>在线用户</a> | <a href='top.c'>在线高手</a> | <a href='topten.c'>TOPTEN</a></td></tr>\n";
        return ret;
}
