//by Canoe on 01-06-21.
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","С  ·");
	set("long",@LONG
������һ���ľ���С·��·��ȫ����Щ�滨��ݣ�����ǰ��
����ԼԼ��Ƭ�ݵء��㲻�ɵ���ȥ���������̺����������ţ�����
���ˡ�������,Ҫ��ȥ�Ļ�ֻ����(tiao)��ȥ.
LONG
);
	
set("exits", ([ /* sizeof() == 2 */
  "north":__DIR__"road2",
        
]));
 set("objects", ([
    "/d/liandan/obj/baicaoxian1" : random(2) ,
    "/d/liandan/obj/xianguan" : random(3) ,
         ]));
 
	setup();
}
void init()
{
add_action("do_jump", "tiao");
}

int do_jump(string arg)
{
	object me=this_player();
	
if( !arg || (arg!="cliff" && arg!="����") )
		return notify_fail("��Ҫ�������\n");
	if(me->is_fighting()||me->is_busy()||me->query_temp("pending"))
		return notify_fail("���æ����ʲôѽ��\n");
        if((int)me->query("learned_points")<200000)
                return notify_fail("�������ѧ,�ƺ����е㲻��,������Ǻ�Σ�յ�Ŷ��\n");
         
message_vision("$N�������˼�����һ�����,�����Ṧ�ڿն���\n", me);
	me->move("/d/penglai/yaxia");
message_vision("$N���ȵ����ش���������������\n", me);
return 1;

}
