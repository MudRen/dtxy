/*
	www/cgi-bin/inc_header.c
	Created by Ammy@YSZZ
	2001/04/13
	��ÿ��ҳ��Ķ�������
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

        if(d) time = chinese_number(d) + "��";
        else time = "";

        if(h) time += chinese_number(h) + "Сʱ";
        if(m) time += chinese_number(m) + "��";
        time += chinese_number(s) + "��\n";
        return time;
}

string gateway()
{
        string ret;

        ret="<head><title>"+MUDLIB_NAME+"���߲�ѯ</title>\n<meta http-equiv='content-type' content='text/html; charset=gb2312'></head>\n\n";
        ret+="<table align='center' border='0' cellPadding='0' cellSpacing='0'width='100%'>\n<td align='center' valign='top' width='50%'>\n<table border='0' cellPadding='2' cellSpacing='0'>\n";
        ret+="<tr><td align='center'><font face='����' style='font-size:16pt'><b><a href='http://ywxrzrdtxy.jumbocool.com/'>���� "
             + MUDLIB_NAME+ "��ҳ</a></b></font></td></tr>\n";
        ret+="<tr><td>&nbsp;</td></tr><tr><td align='center'><b>"+MUDLIB_NAME
             +"ʵʱ���߲�ѯ</b></td></tr><tr><td align='center'>��ǰ����Ϸ�Ѿ������������ " + report()
             + "</td></tr><tr><td>&nbsp;</td></tr><tr><td align='center'><a href='board_list.c'>���԰�</a> | <a href='wizlist.c'>��ʦ�б�</a> | <a href='who.c'>�����û�</a> | <a href='top.c'>���߸���</a> | <a href='topten.c'>TOPTEN</a></td></tr>\n";
        return ret;
}
