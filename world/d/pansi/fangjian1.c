// fangjian1.c
// by lestat/2001.1.31

inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", CYN"������"NOR);
        set("long", @LONG
���Կ���������ǰ������һ������ĵط����������һ��ʯ������ֻ��
��֮�⣬�յ�����һ�����У�ʯ���Ͽ����ݺ�ʮ�ŵ���·������ϲ���
�������ӣ���Ȼ��һ�ָտ�ʼ�µ��塣
LONG );
	set("exits", ([
		"south" : __DIR__"shiji1",
	]));
        set("objects",([
//                "/d/dntg/sky/npc/yuntong" : 1,
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
