// Room: /d/death/walk.c
#include <ansi.h>

inherit ROOM;

void create ()
{
  set ("short", HIR"���Ź�"NOR);
  set ("long", @LONG

��Լ�����ֳ�һ����ɫ��¥����¥����һ�����ң�������š���ڤ
�硱�������֡���¥�³��Ž��գ��������ʲôҲ���������·��
һ����ľ��ֱֱ��ָ�򱱷�����Χֻ��������ɫ�Ļ����������
����˸�š�
LONG);

  set("exits", ([ /* sizeof() == 3 */
  "east" : __DIR__"new-out5",
  "west" : __DIR__"new-out7",
  "south": __DIR__"gate",
]));
  set("hell", 1);

  setup();
}

void init()
{
        //object me=this_player();
	//	remove_call_out("greeting");
        //        call_out("greeting", 60, me);
	add_action("do_pass", "north");
	add_action("do_break", "break");
}
void greeting(object ob)
{
        if( !ob || environment(ob) != this_object() ) return;
	ob->set_temp("time_enough", 1);
	return;
}
int do_pass()
{
	object me=this_player();
	
	//if( me->is_ghost() && !me->query_temp("time_enough") )
	//	return notify_fail("��¥����Լ��������������̫ʢ��������ǣ�\n");

	//if( me->is_ghost() ) {
	//	me->reincarnate();
	//	me->set("gin", (int)me->query("max_gin"));
	//	me->delete_temp("time_enough");
	//}

	tell_object(me, "��ֱֱ���򱱶��ų�����ȥ����Ȼ���ֺ�ɫ�ĳ���ֻ�ǵ�����������\n");
	tell_room(environment(me), me->name()+"ֱֱ���򱱶��ų�����ȥ����Ȼ�ӽ��յ����д��˹�ȥ��\n",
({me, me}));
	me->move("/d/death/new-zhaopo");
	tell_room(environment(me), me->name()+"���˹�����\n", ({me, me}));
	return 1;
}

int do_break()
{
	object me=this_player();
	if( !me->query_temp("jingtian/jiejie") )
		return 0;
	if( me->is_busy() )
	{
		tell_object(me, "����æ���ء�����\n");
		return 1;
	}
	if( me->query("force") < 1000 )
	{
		tell_object(me, "������̫���ˡ�����\n");
		return 1;
	}
	me->start_busy(2);
	me->add("force",-100);
	message_vision("$N��������Ż��£�\n",me);
	if( random(me->query("kar")) > 25 )
	{
		message_vision("���ŷ���һ�����죬����˷�ĩ�������ֱ����紵ɢ�ˣ�\n",me);
		me->delete_temp("jingtian");
		if( random(me->query("int")) > 17 )
		{
			me->add("jingtian_known",1);
			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"�� ��ʴ��(yuhuang dadi)�����²��ã�" + me->name() + "�ѹ��ŹصĽ������ˣ��Ͻ�ȥ��������������һ�������Բߣ�\n\n"NOR,users());
   			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��ڤ��(ming wang)��" + me->name() + "������Źؽ�磬�������������ظ�������ѧ����"+HIB"[������ʽ����"HIB"���"HIR"��ŭ"HIC"ʽ"HIB"]"+HIC"��\n\n"NOR,users());
   			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��ڤ��(ming wang)��ڤ�������Ϊ������ڤ��Ӵ˺�����ͥ����綦�����֣�\n\n\n"NOR,users());
		}
		else
		{
			me->set("jingtian_cant",1);
			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"�� ��ʴ��(yuhuang dadi)�����²��ã�" + me->name() + "�ѹ��ŹصĽ������ˣ��Ͻ�ȥ��������������һ�������Բߣ�\n\n"NOR,users());
   			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��ڤ��(ming wang)��" + me->name() + "������Źؽ�磬�������������ظ�����ϧ���������ظ�Թ�����޷�����"+HIB"[������ʽ����"HIB"���"HIR"��ŭ"HIC"ʽ"HIB"]"+HIC"��\n\n"NOR,users());
   			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��ڤ��(ming wang)��ڤ�������Ϊ������ڤ��Ӵ˺�����ͥ����綦�����֣�\n\n\n"NOR,users());
		}
	}
	else
		message_vision("�����Ϸ���������������һ���ֹ���ƽ����\n",me);
	return 1;
}