// Room: /d/menggu/yading
#include <ansi.h>
inherit ROOM;

void create()
{
  set ("short", "ɽ�¶�");
  set ("long", @LONG
�¶��Ǹ��޴��ƽ̨�������˰�����ѩ������޴��ʯͷ������һ��,
��״ǧ��ٹ�,��������ප����С��,�����,��������.�ıߵ�ɽ��ƽƽ
����,���ð�����б�����±�.
LONG);
	set("objects", ([ /* sizeof() == 1 */
        __DIR__"npc/fengxue.c" : 1,
]));

  set("outdoors", "menggu");
  setup();
}
void init()
{
	add_action("do_jump","jump");
}

int do_jump(string arg)
{
	int i;
	object *inv;
        object ob;
        ob = this_player();
        if( !arg || arg=="" ) return 0;
        if( ob->query_temp("julong_ask")!=1 ) return 0;
        if( (int)ob->query("combat_exp")<3000000 ) return 0;
        inv = all_inventory(ob);
        for(i=0; i<sizeof(inv); i++)
                {	if (inv[i]->is_character() )
                	{message("vision", NOR"�㻹�ǵȻ������ɣ�\n"NOR,ob);
			return 1;}
                }
        if( arg != "down" )
                return notify_fail("����Ҫ������ɱ����ô�벻������\n");
        tell_object(ob, HIR"�㲻��˼��������һԾ�����������¡�������\n"NOR);
        message("vision", NOR"ֻ��" + ob->query("name") + "��������������֮�С�������\n"NOR, environment(ob), ob);
        if((ob->query_skill("dodge",1)<30))
        	ob->unconcious();
        ob->move(__DIR__"entrance");
        return 1;
}


