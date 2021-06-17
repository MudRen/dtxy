inherit ROOM;
#include <ansi.h>
void create ()
{
  set ("short", "�κ���");
  set ("long", @LONG

����һ��������֮������֮����ʯ�š����к������������
Ѫ�����ϡ����������޷��֣��վ�֮·��ͬƥ�����������
֮ˮ�������ˣ��ȷ��˱ǡ�
LONG);

  set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"bidouya",
  "north" : __DIR__"huangwai",
]));
  set("hell", 1);
  set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/shizhe" : 2,
]));

  setup();
}

void init()
{
        add_action("do_xiulian", "xiulian");
}
int do_xiulian()
{       
        object me=this_player();
	if( !me->query_temp("jingtian/lingwu") )
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
	me->start_busy(5);
	me->add("force",-100);
	message_vision("$N��ϥ���£�׼�������κ����ϵĳ�Թ���֮����\n",me);
	if( random(me->query("kar")) > 25 )
	{
		message_vision(HIR"���µ�Ѫ��ͻȻ����������Ѫ�����죬�м仹����ɭɭ�׹ǣ�\n"NOR,me);
		message_vision(HIR"��������ʹ�߻����񣺵��꣬����ڤ����������������˾����ѧ��������龳���ѵ�������\n"NOR,me);
		me->delete_temp("jingtian");
		if( random(me->query("int")) > 25 )
		{
			me->add("jingtian_known",1);
			message_vision(HIR"$N��Ѫ���е���Ϣ�������壬�����쳣�������\n"NOR,me);
   			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��ڤ��(ming wang)��" + me->name() + "���Թ��ˣ����������������ظ������ķ�����ѧ����"+HIB"[������ʽ����"HIB"�ϳ�"HIR"����"HIC"ʽ"HIB"]"+HIC"��ǰ;����������\n\n"NOR,users());
   			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��ڤ��(ming wang)����������ڤ���ֶ�һ�������֣�ͳһ�����ʱ�����ˣ�\n\n\n"NOR,users());
		}
		else
		{
			me->set("jingtian_cant",1);
			message_vision(HIR"$N��Ѫ���е���Ϣ�������壬ֻ��������θ���۵��³�һ����Ѫ��\n"NOR,me);
   			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��ڤ��(ming wang)��" + me->name() + "���Բ��㣬�޷���ȫ�����������ظ������ķ�����δ��ѧ��"+HIB"[������ʽ����"HIB"�ϳ�"HIR"����"HIC"ʽ"HIB"]"+HIC"�����ǿ�ϧ��\n\n"NOR,users());
   			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��ڤ��(ming wang)����������ͳһ�����ʱ��δ������ڤ�������ӽ�������\n\n\n"NOR,users());
		}
	}
	return 1;
}

