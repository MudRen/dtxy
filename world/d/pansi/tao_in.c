//2001.2.2
//lestat
#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
        set("short", HIM"�һ�����"NOR);
        set("long",
"����һƬ"+HIM"�һ�"NOR+"�ĺ�������һ���޼ʣ�ȫ��ʢ����"+HIM"�һ�"NOR+"��΢�������
��Ӣ�ͷס���Χ�����ĵġ������ߺ����и����ԡ�Զ��ż������һ��
��С�������һƬ"+HIM"�һ�"NOR+"�֣�����ԶԶ������ֻ���ӡ�\n"
           );
       set("exits", ([
           "south" : "/d/dntg/hgs/houshan3",
           "north" : __DIR__"tao0",
           "east" : __DIR__"taob",
           "west" : __DIR__"taoa",
       ]));
	   set("objects",([
		__DIR__"npc/xiang" : 1,
		__DIR__"obj/guo" : 3,
	]));


       set("outdoors","taohua");
       set("no_clean_up", 0);
       setup();
       replace_program(ROOM);
}

