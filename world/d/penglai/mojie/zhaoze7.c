#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
 set("short", "������");
 set("long", @LONG
��������Ϳ�Ҫ����ħ��������ˣ�����һ·���һ��棬���ﾹȻ���ǹι�һ�󺮷磬��������ǴӲ�Զ����һ���޴�Ķ�Ѩ�г����ġ�
LONG
 );
 set("exits", ([
  "east" : "/d/penglai/mojie/zhaoze6",
  "enter" : "/d/penglai/mojie/center",
]));
 
 setup();
}
