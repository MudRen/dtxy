// Room: some place in ��ţ����
// forrest.c
#include <room.h>
inherit ROOM;
#include <ansi.h>
int do_jie();
void create()
{
  set ("short", "����ɽ");
  set ("long", @LONG

������һƬҰ���֣�ɽ�е��������˲�ժ�����ܵ����ӹ���֦
ͷ�����µ����Ѹ��ó��࣬��֪�Ѽ��˼����ꡣ
��������һ�����Ӳӵķ�ӡ��������Խң�jie��������
LONG);
set("exits", ([ /* sizeof() == 4 */
"eastdown" : __DIR__"lantao",

]));

set("objects", ([ /* sizeof() == 2 */
"/d/lingtai/npc/swk": 1]));
  
      //set("no_clean_up", 0);
	set("outdoors", 1);
        setup();
        //replace_program(ROOM);
}
void init()
{
        add_action("do_jie","jie");
}
int do_jie()
{
	object me = this_player();
	object jingang;
	if( !me->query_temp("huohun/yuanshen") )
		return 0;
	else if( me->query_temp("huohun/mu") )
	{
		message_vision("\n�����ӡ���Ѿ�����ҿ��ˣ�\n",me);
		return 1;
	}
	else
	{
		me->add_temp("huohun/yuanshen",1);
		me->set_temp("huohun/mu",1);
		message_vision(HIY"\n$N���Ὣ��ӡ�ҿ���һ����â�ɳ�������ɽ����ƶ������ȥ��\n"NOR,me);
		message_vision(HIY"\n��Ȼ������������������λ��գ������ȵ���˭��˽�Խҿ���ӡ����\n",me);
		jingang = new("/d/qujing/kusong/npc/jingang");
		jingang->move(environment(me));
		jingang->kill_ob(me);
		jingang = new("/d/qujing/kusong/npc/jingang");
		jingang->move(environment(me));
		jingang->kill_ob(me);
		return 1;
	}
}
