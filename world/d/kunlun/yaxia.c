#include <ansi.h>
inherit ROOM;
int do_jie();
void create ()
{
  set ("short", "������");
  set ("long", @LONG
    ��ϼɢ�ʣ�����ҡ�⣻ǧ���ϰأ��������ǧ���ϰأ�������ɽ��ȾȾ���������
����һ��ɫ�Բԡ������滨�������ű��������㣻������Һ���ã������ײݴ�˿����ʱ��
�ɺ�ণ�ÿ������裻�ɺ��ʱ�������������Զ������账��ë����ɫ���ƹ⡣��¹��Գ
ʱ���֣���ʨ�������вأ�ϸ���鸣�أ�����ʤ���á�
	ɽ�±��ϣ���һ�����Ӳӵķ�ӡ��������Խң�jie��������
LONG);

  set("outdoors", 1);
  set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"xiaolu1",
]));

  setup();
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
	else if( me->query_temp("huohun/jin") )
	{
		message_vision("\n�����ӡ���Ѿ�����ҿ��ˣ�\n",me);
		return 1;
	}
	else
	{
		me->add_temp("huohun/yuanshen",1);
		me->set_temp("huohun/jin",1);
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