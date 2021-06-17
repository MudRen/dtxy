// yashi.c
#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
  set ("short", "����");
  set ("long", @LONG

��С����Է���������Է��𣮣���ǰվ��һλŮ�ӣ�����
�������Ŵ�����񣬿�����һ���ؾ��Ĵ���(bed)�����յ���
�ز���һ����Ӱ������
LONG);

set("item_desc",(["bed":"˯���õĴ���(gosleep,gobed,bed)�� \n", ]));
set("exits", ([ /* sizeof() == 4 */
"down" : __DIR__"guige",
]));

set("objects", ([ /* sizeof() == 1 */
"/d/gao/npc/gaoxiaojie" : 1,
]));

create_door("down", "������", "up", DOOR_CLOSED);
        set("no_clean_up", 0);
        setup();
//        replace_program(ROOM);
}

void init()
{
	add_action("do_bed", "gosleep");
	add_action("do_bed", "gobed" );
	add_action("do_bed", "bed");
	add_action("do_zuoyao", "zuoyao");
}

int do_bed()
{       object me;
        me=this_player();
      	message_vision(HIY "$N�ƿ�ɴ�ʣ�׼���ϴ��ˡ�\n\n" NOR, me);
  	me->move("/d/gao/bed_yashi");
            message_vision(HIY "\nɳ������һ����$N���˽�����\n" NOR, me);
         	return 1;
}

int do_zuoyao()
{
	object me=this_player();
	object ob;
	if (me->query_temp("obstacle/zhutou")==1)
        return 1;

	if (me && (me->query_temp("obstacle/gao_asked")==1) && (me->query_temp("apply/name")[0] == "��С��"))
	{
		message_vision("$N���������ڹ���һ�źڷ磬һ����Ӱ�Ӵ������˽���\n",me);
		ob=new("/d/gao/npc/zhu");
		ob->move("/d/gao/yashi");
		 me->start_busy(1+random(2));
                 me->set_temp("obstacle/zhutou",1);

	}
	else
	{
		message_vision("$N�ڴ������˰���ʲôҲû������\n",me);
	}
	return 1;
}