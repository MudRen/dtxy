// By Canoe 2001-06-21
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","��ũҩ��");
	set("long",@LONG
������һ��ҩ��,������������ҩ�㡣���������де�
����ҩ��,Ҳ���������﷢��Щ��ҩ��
LONG
);
	
	set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"baihuagu10",
  "west":__DIR__"baihuagu11",
  "east":__DIR__"baihuagu12",
  "south":__DIR__"road2",  
]));
	setup();
}
