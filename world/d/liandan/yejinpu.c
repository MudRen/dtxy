// By canoe 2001-06-21
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","ұ����");
	set("long",@LONG
������ũ�����ұ����, һ��Ƥ����ڵ�������
�������µش����Ų�֪������ʲ,��ũ�ϲɼ��ٲ���
Ҫ��ҩ�������������ġ�������, ���ܹ�����
ҩ��.
LONG
);
	
	set("exits", ([ /* sizeof() == 2 */
  "west": __DIR__"road2",
        
]));
 set("objects", ([
    "/d/liandan/obj/tiejiang" : 1 ,
    "/d/liandan/obj/xianguan" : random(2) ,
         ]));
 
setup();
}
