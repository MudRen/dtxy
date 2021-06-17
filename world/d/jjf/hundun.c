#include <ansi.h>
#include <room.h>
inherit ROOM;
int do_lingwu();
int finish(object who);
int finish2(object who);
void create()
{
set("short", "����");
set("long", @LONG
    
����ռ����̹�ʹ���Լ���������������ġ�
�͵����̹ų������ƿ��Ļ���ǳ����ơ�
�������������������lingwu����һЩ������
 
LONG );
setup();
}
void init() 
{
    add_action ("do_lingwu","lingwu");
}

int do_lingwu()
{
  	object who = this_player();
  	if( who->query("kai_cant") )
  	{
  		message_vision(HIY"��Կ���ٵص���ʶ���Ѿ�������ļ��ޡ�\n"NOR,who);
  		return 1;
  	}
  	if( !who->query_temp("kai_learn") )
  	{
  		message_vision(HIY"������ô�����ģ���\n"NOR,who);
  		return 1;
  	}
  	if( who->query_temp("kai_learning") )
  	{
  		message_vision(HIY"����������\n"NOR,who);
  		return 1;
  	}
  	message_vision(HIY"$N��ϸ����������ʼ��״̬����������������\n"NOR,who);
	who->set_temp("kai_learning",1);
	who->start_busy(20);
	if( !who->query("kai_known") && random(who->query("int")) > 20 - random( who->query("lunhui_zhuanshi") ) )
		call_out("finish",10,who);
	else if( who->query("kai_known") == 1 && random(who->query("int")) > 25 - random( who->query("lunhui_zhuanshi") ) )
		call_out("finish",10,who);
	else if( who->query("kai_known") == 2 && random(who->query("int")) > 30 - random( who->query("lunhui_zhuanshi") ) )
		call_out("finish",10,who);
	else
		call_out("finish2",10,who);
	return 1;
}

int finish(object who)
{
	object downroom = load_object(__DIR__"sleep");
	if(base_name(environment(who)) != "/d/jjf/hundun")
	{
		message_vision(HIY"$N�뿪�˻��磬�����жϡ�\n"NOR,who);
		who->delete_temp("kai_learning");
		who->delete_temp("kai_learn");
		return 1;
	}
	message_vision(HIY"$N�����̹Ÿ�ͷ�����ķ�ʽ��������������\n"NOR,who);
	message_vision(HIY"�̹ŵĶ�����ͣ����$N�Ժ����طţ�\n"NOR,who);
	message_vision(HIY"$N��Ȼ�����̹���������ٵ�ʵ��Ҫ��ԭ�ڻ���Ĺ�����\n"NOR,who);
	if( !who->query("kai_known") )
	{
		message_vision(HIY"$Nһ����Х������������ȴ�������Լ��Ĺ�����Ȼ�޷���̣�\n"NOR,who);
		message_vision(HIY"ͻȻ$N�ָ��ܵ�����Χ�����磡\n"NOR,who);
		who->set("kai_known",1);
		who->delete_temp("kai_learn");
     		who->delete_temp("kai_learning");
		who->move("/d/jjf/sleep");
		message_vision(HIY"һ����Ӱ��ͻȻ����������ǰ��\n"NOR,downroom);
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"���̹�(pan gu)��" + who->name() + "��������Ŭ��������������"+HIM"[����ٵ�]"+HIC"��\n\n\n"NOR,users());
		return 1;
	}
	if( who->query("kai_known") == 1 )
	{
		message_vision(HIY"$Nһ����Х������������ȴ�������Լ��Ĺ�����Ȼ�޷���̣�\n"NOR,who);
		message_vision(HIY"ͻȻ$N�ָ��ܵ�����Χ�����磡\n"NOR,who);
		who->set("kai_known",2);
		who->delete_temp("kai_learn");
     		who->delete_temp("kai_learning");
		who->move("/d/jjf/sleep");
		message_vision(HIY"һ����Ӱ��ͻȻ����������ǰ��\n"NOR,downroom);
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"���̹�(pan gu)��" + who->name() + "��������Ŭ������"+HIM"[����ٵ�]"+HIC"�����������һ�����Σ�\n\n\n"NOR,users());
		return 1;
	}
	if( who->query("kai_known") == 2 )
	{
		message_vision(HIY"$Nһ����Х�������ĸ���ȴ�������Լ��Ĺ�����Ȼ�޷���̣�\n"NOR,who);
		message_vision(HIY"ͻȻ$N�ָ��ܵ�����Χ�����磡\n"NOR,who);
		who->set("kai_known",3);
		who->delete_temp("kai_learn");
     		who->delete_temp("kai_learning");
		who->move("/d/jjf/sleep");
		message_vision(HIY"һ����Ӱ��ͻȻ����������ǰ��\n"NOR,downroom);
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"���̹�(pan gu)��" + who->name() + "��������Ŭ��������������"+HIM"[����ٵ�]"+HIC"ȫ��������\n\n\n"NOR,users());
		return 1;
	}
	return 1;	
}

int finish2(object who)
{
	object downroom = load_object(__DIR__"sleep");
	if(base_name(environment(who)) != "/d/jjf/hundun")
	{
		message_vision(HIY"$N�뿪�˻��磬�����жϡ�\n"NOR,who);
		who->delete_temp("kai_learning");
		who->delete_temp("kai_learn");
		return 1;
	}
	message_vision(HIY"$N�Լ���������ռ䣬��ĥ���������İ취��\n"NOR,who);
	message_vision(HIY"$N���ϵ������̹ų��ֵķ�ʽ�����ϵ������ſռ����ǣ�\n"NOR,who);
	message_vision(HIY"��ϧ$NŬ������ã�����ռ�Ҳû���ɶ�������$N�Ѿ���ƣ�����ˣ�\n"NOR,who);
	message_vision(HIY"ͻȻ$N�ָ��ܵ�����Χ�����磡\n"NOR,who);
	who->set("kai_cant",1);
	who->delete_temp("kai_learn");
     	who->delete_temp("kai_learning");
     	if( !who->query("kai_known") )
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"���̹�(pan gu)��" + who->name() + "�Խ�̫�������Բ��㣬�޷�����"+HIM"[����ٵ�]"+HIC"�����ǿ�ϧ����\n\n\n"NOR,users());
	else
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"���̹�(pan gu)��" + who->name() + "�Խ�̫�������Բ��㣬�޷�������ߵ�"+HIM"[����ٵ�]"+HIC"�����ǿ�ϧ����\n\n\n"NOR,users());
	message_vision(HIY"һ����Ӱ��ͻȻ����������ǰ��\n"NOR,downroom);
	who->move("/d/jjf/sleep");
	who->unconcious();
	return 1;	
}