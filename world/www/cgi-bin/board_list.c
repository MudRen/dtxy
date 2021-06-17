/*
  www/cgi-bin/board_list.c
  By Ammy@YSZZ
  2001/04/13
  ʹ��ʱ��ȷ���������԰������ļ�������
  modified by emotion
 */

#include <mudlib.h>

inherit F_CLEAN_UP;
//inherit F_REMOVEANSI;

private mapping vaild_boards = ([
        "ann_b" :       ({"��ʦ������",0}),
        "nancheng_b" :      ({"�ϳǿ�ջ���԰�",1}),
        "dragon_b" :    ({"�����ĺ����԰�",1}),
        "jiangjing_b" : ({"��ׯ�۽�����",1}),
        "moon_b" :      ({"�¹����԰�",1}),
        "shengsi_b" :   ({"�ظ�������",1}),
        "shibei_b" :    ({"��̨ɽʯ��",1}),
        "system_b" :    ({"ϵͳ�����",0}),
        "wall_b" :      ({"�������Ա�",1}),
        "jjf_b" :      ({"���������Ͳ�",1}),
        "hyd_b" :      ({"���ƶ����԰�",1}),
        "wudidong_b" :      ({"�޵׶��˱�",1}),
        "jian_b" :      ({"ɢ�ɽ���",1}),
        "sword_b" :      ({"��ɽ�⽣��",1}),
        "lei_b" :      ({"��˿����ʯ",1}),
        "yubi_b" :      ({"����ɽ���",1}),
        "xueshan_b" :   ({"ѩɽ���԰�",1}),

]);


string gateway() {
        int i,j=0;
        string str,str_h,str_f,*list;
        string number,master,time;
        mapping notes;
        str_h="/www/cgi-bin/inc_header.c"->gateway();
        str_f="/www/cgi-bin/inc_footer.c"->gateway();

        list = keys(vaild_boards);
        sort_array(list,1);

        str =str_h;
        str+="<table width=100% border=0>";
        str+="<tr><td align=right><span style='font-size:9pt'>";
        str+=read_file("/log/counter_for_web");
        str+="&nbsp;&nbsp;</span></td></tr></table>";

        str += "<table border=0 width='95%' cellspacing=0 cellpadding=0 align=center>";
        str += "<tr><td>";
        str +="<table border=0 width='100%' cellspacing=1 cellpadding=4>";

        str +=sprintf("
        <tr>
           <td align=center bgcolor='#fafafa' nowrap><font
          color='#339900'> ��� </font></td>
          <td align=center bgcolor='#fafafa' nowrap> <font color='#339900'> ����
            </font> </td>
          <td align=center bgcolor='#fafafa' nowrap> <font color='#339900'> ��ʽ
            </font></td>
          <td align=center bgcolor='#fafafa' nowrap> <font color='#339900'> ���¼���
            </font></td>
          <td align=center bgcolor='#fafafa' nowrap> <font color='#339900'>�Ұ�����</font></td>
        </tr>"
        );

        str += sprintf(
        "<tr>
          <td bgcolor='#ccff99' colspan='6'><b><span style='font-size:11pt'><font color='#339900'>�� %s�﹫����</font></span></b></td>
         </tr>",
         MUDLIB_NAME
         );
        for (i=0;i<2;i++)
        {

                if(i==0) list[i]="ann_b";
                if(i==1) list[i]="system_b";
                str +="<tr>";
                number="/www/cgi-bin/board_h.c"->gateway(list[i],"num");
                master="/www/cgi-bin/board_h.c"->gateway(list[i],"master");
                time="/www/cgi-bin/board_h.c"->gateway(list[i],"time");
                str +=  sprintf(
                "<td align=left>%d.<a href=board_read?%s&0&9999>%s</a></td>"
                "<td align=center>%s</td>"
                "<td align=center>%s</td>"
                "<td align=center>%s</td>"
                "<td align=center>%s</td>"
                "</tr>",
                                j,
                                list[i],
                                vaild_boards[list[i]][0],
                                number,
                                vaild_boards[list[i]][1]==1?"��д":"ֻ��",
                                time,
                                master
                                );
        }

        str += sprintf(
        "<tr>
          <td bgcolor='#ccff99' colspan='6'><b><span style='font-size:11pt'><font color='#339900'>�� %s������������</font></span></b></td>
         </tr>",
         MUDLIB_NAME
         );

                str +="<tr>";
                number="/www/cgi-bin/board_h.c"->gateway("nancheng_b","num");
                master="/www/cgi-bin/board_h.c"->gateway("nancheng_b","master");
                time="/www/cgi-bin/board_h.c"->gateway("nancheng_b","time");
                str +=  sprintf(
                "<td align=left>%d.<a href=board_read?%s&0&9999>%s</a></td>"
                "<td align=center>%s</td>"
                "<td align=center>%s</td>"
                "<td align=center>%s</td>"
                "<td align=center>%s</td>"
                "</tr>",
                                j,
                                "nancheng_b",
                                vaild_boards["nancheng_b"][0],
                                number,
                                vaild_boards["nancheng_b"][1]==1?"��д":"ֻ��",
                                time,
                                master
                                );


        for( i=0;i<sizeof(list);i++)
        {

        if (list[i]=="ann_b" || list[i]=="system_b" || list[i]=="nancheng_b") continue;

        ++j;
        str +="<tr>";

/*
  the first: board's name ,decribtion,url,order number
  the second: the number of all posts in this board
  the third:  the limiting of this board
  the 4th:  time of the last post
  the 5th:  the  master's id of this board
*/

        number="/www/cgi-bin/board_h.c"->gateway(list[i],"num");
        master="/www/cgi-bin/board_h.c"->gateway(list[i],"master");
        time="/www/cgi-bin/board_h.c"->gateway(list[i],"time");
        str +=  sprintf(
        "<td align=left>%d.<a href=board_read?%s&0&9999>%s</a></td>"
        "<td align=center>%s</td>"
        "<td align=center>%s</td>"
        "<td align=center>%s</td>"
        "<td align=center>%s</td>"
        "</tr>",
                                j,
                                list[i],
                                vaild_boards[list[i]][0],
                                number,
                                vaild_boards[list[i]][1]==1?"��д":"ֻ��",
                                time,
                                master
                                );

        }

        str += "</table></table></center>";
        str +=str_f;
        return str;
}

mapping query_boards() {
        return vaild_boards;
}
