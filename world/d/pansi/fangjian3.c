// �׹Ƕ�
// by lestat 2001
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", HIW"�׹Ƕ�"NOR);
        set("long", @LONG
������ɭɭ�ģ��������ˣ����������ܰ��Ź���λ���žŶ�����ͷ��ÿ�Ѿ�
������ͷ���²�������в��������ϲ�
һ����ģ�����ǹ��档������
LONG );
	set("exits", ([
		"east" : __DIR__"tongmen",
	]));
	set("objects",([
		__DIR__"npc/bai" : 1,
//		"/d/dntg/sky/npc/fengpo" : 1,
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
