// by HAPP@YSZZ
#include <ansi.h>
inherit ROOM;
int block_cmd(string);
void create ()
{
        set ("short", "���Ĺ���з��");
        set ("long", @LONG
    ��˹���˼�Ů������÷�����˶��Ӻ�����˹��������˹�����͵±��Ĺ�����飬����
С���������������������˹������������������˹���������ޣ��Լ�Ҳ������ɱ
����˹Ϊ���������������ΪҮ��˹��˹���������辭��ʮ����ð���ж������еڶ���
���Ʒ�ס�������еĹ�������������������ֻ�оŸ�ͷ�ľ��ߣ��������󸽽��Ķ����ڣ�
������˹����Ͷ��棬��ŭ�����������¶���������ͬס��������Ĵ��з�ۼ���������
ս��������ҧ������˹�Ľţ������з�����飬������Ҳ���Ʒ����������������������
��������������з����

LONG);


        set("exits", ([
        "eastup"    :       __DIR__"jx2sz1",
        "southdown"  :       __DIR__"sz2jx2",        
        ]));

        set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/juxie" : 1,
        ]));
        set("outdoors", "12gong");
        setup();
}

int valid_leave(object me, string dir)
{
        if ( present("ju xie") && dir == "eastup" )
        return notify_fail("��˹��˹��:�ȹ��������˵��\n");
        return ::valid_leave(me, dir);
}

void init()
{
    add_action("block_cmd", "", 1);
}
int block_cmd(string args)
{
string verb;
verb = query_verb();
    if (verb == "recall") return 1;
    return 0;
}
