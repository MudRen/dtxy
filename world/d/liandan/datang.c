// By canoe 2001-06-21
#include <room.h>
inherit ROOM;

void create()
{
set("short", "��  ��");
set("long", @LONG
    
��������ũ��ׯ԰�Ĵ���,��ϧû�������������ǽ��
����һ¯̴�㣬һ˿�������޵������������ơ�����¯
�İ���ʮ�ֹ⻬,�ƺ��������˽Ӵ�.

LONG );
set("exits", ([
  "east": __DIR__"road2",
]));
set("item_desc", ([ /* sizeof() == 1 */
  "xianglu" : "
һ�����ص���¯,���������ƶ�(move)��.
"]));
  set("objects", ([ /* sizeof() == 4 */
       __DIR__"obj/xianguan" : 2,
]));
setup();
}
void init()
{
add_action("do_move", "move");
}

int do_move(string arg)
{
	object me=this_player();
	
if( !arg || (arg!="xianglu" && arg!="��¯") )
		return notify_fail("��Ҫ�ƶ�ʲô��\n");
	if(me->is_fighting()||me->is_busy()||me->query_temp("pending"))
		return notify_fail("���æ����ʲôѽ��\n");
        if((int)me->query("learned_points")<200000)
                return notify_fail("�������ѧ,�ƺ����е㲻��,û��Ҫȥ���棡\n");
        me->start_busy(1+random(2)); 
	message_vision("$N˫�ֱ�ס��¯,��������,��¯������$N�ƶ��ˡ�\n", me);
	if(random(me->query("str"))>5)
	        {
	        message_vision("��¯�¾�Ȼ�м������,$N�Ͽ����˽�ȥ��\n", me);
	        me->move("/d/liandan/danfang");
      tell_room( environment(me), "����ͨ��һ����" + me->name() + "���������ɵ�����������\n",
               ({me}) );
	        }
        else    message_vision("��¯���˻�,�ֺ��һ���ƻ�ԭ����\n", me);	        
return 1;

}
