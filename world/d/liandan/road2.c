// By canoe 2001-06-21
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","С  ·");
	set("long",@LONG
������һ���ľ���С·��·��ȫ����Щ�滨��ݣ�����ǰ��
����ԼԼ��Ƭ�ݵء��㲻�ɵ���ȥ���������̺����������ţ�����
���ˡ��������˿�����(paizi),��������ũ������ҩ�ĵط���
LONG
);
	
	set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"road1",
  "north":__DIR__"road3",
  "west": __DIR__"datang",
  "east":__DIR__"yejinpu",
        
]));
  set("item_desc", ([ /* sizeof() == 1 */
  "paizi" : "
  [1;31m
 	 ������������
    	 ��	    ��
    	 �� ��   �� ��
   	 �� ũ   �� ��
   	 �� ҩ   �� ��
   	 �� ��   �� ��
   	 ��	    ��
    	 ������������
[m
"]));
 set("objects", ([
    "/d/liandan/obj/baicaoxian1" : random(2) ,
    "/d/liandan/obj/baicaoxian2" : random(2) ,
    "/d/liandan/obj/xianguan" : random(2) ,
         ]));
 
setup();
}
