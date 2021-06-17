#include <ansi.h>
#include <room.h>
inherit ROOM;
int do_lingwu();
int check(object who,int k);
int finish(object who);
int finish2(object who);
void create()
{
set("short", "���пռ�");
set("long", @LONG
    
��ռ��ڵ�����������Ԫ�أ��м���һ����ɽ��������ΰ��
 
LONG );
     set("exits/out", __DIR__"dadian");
     set("objects", ([ /* sizeof() == 4 */
       __DIR__"obj/wuxingshan" : 1,
]));
setup();
}
void init() 
{
    call_out ("check_hp", 6+random(5),this_player());
    add_action ("do_lingwu","lingwu");
}
int check_hp(object who)
  {
  object where = this_object();
  if ( (! who)  ||    (! present(who, where)) )  return 1;
  if( who->query("kee") > 100 && who->query("sen") > 100 )
    {
    	switch (random(6))
        {
        	case 0:
                { 
                       	message_vision(HIB"\n��������Ԫ��һ����ң�����һ��Ԫ�ط籩��$N�����Ķ������ᣡ\n"NOR,who);
                       	who->receive_damage("kee",50);
                      	who->receive_damage("sen",50);
                      	COMBAT_D->report_status(who);
                      	COMBAT_D->report_sen_status(who);
                        break;
               	}
               	case 1:
                { 
                       	message_vision(HIB"\n���ܽ�Ԫ������һ��������$N���̵ı������ˣ�\n"NOR,who);
                       	who->receive_damage("kee",50);
                      	COMBAT_D->report_status(who);
                        break;
               	}
               	case 2:
                { 
                       	message_vision(HIB"\n����ˮԪ�ػ�۳�һ��������$N����Ķ������ᣡ\n"NOR,who);
                       	who->receive_damage("kee",50);
                      	COMBAT_D->report_status(who);
                        break;
               	}
               	case 3:
                { 
                       	message_vision(HIB"\n����ľԪ������һƬ������$N�����ı������ˣ�\n"NOR,who);
                       	who->receive_damage("kee",50);
                      	COMBAT_D->report_status(who);
                        break;
               	}
               	case 4:
                { 
                       	message_vision(HIB"\n���ܻ�Ԫ������һ����ǽ��$N���յĽ�ͷ�ö\n"NOR,who);
                       	who->receive_damage("kee",50);
                      	COMBAT_D->report_status(who);
                        break;
               	}
               	case 5:
                { 
                       	message_vision(HIB"\n����һֱ�ض�ɽҡ��$N��ҡ�Ķ������ᣡ\n"NOR,who);
                       	who->receive_damage("kee",50);
                      	COMBAT_D->report_status(who);
                        break;
               	}
	}
    }
  if ( (100*(who->query("kee")))/(who->query("max_kee")) <= 10)
    {
     	message_vision(HIY"$Nʵ�ڼ�ֲ�ס�ˣ�����Ͼ����ҡ�\n"NOR,who);
     	message_vision(HIY"$N��ǰ����һ�����뿪�����пռ䡣\n"NOR,who);
     	who->delete_temp("wuxing_learn");
     	who->delete_temp("wuxing_learning");
     	who->move("/d/33tian/dadian");
     	who->unconcious();
     	return 1;
    }
  	remove_call_out ("check_hp");
  	call_out ("check_hp", 6+random(5),who);
  	return 1;
  }
int do_lingwu()
{
  	object who = this_player();
  	if( who->query("wuxing_cant") )
  	{
  		message_vision(HIY"������е���ʶ���Ѿ�������ļ��ޡ�\n"NOR,who);
  		return 0;
  	}
  	if( !who->query_temp("wuxing_learn") )
  	{
  		message_vision(HIY"û��̫���Ͼ�����������˽������\n"NOR,who);
  		return 0;
  	}
  	if( who->query_temp("wuxing_learning") )
  	{
  		message_vision(HIY"����������\n"NOR,who);
  		return 0;
  	}
  	message_vision(HIY"$N��ϸ�۲�����������Ԫ�صĹ��ɣ����������������е��������档\n"NOR,who);
	who->set_temp("wuxing_learning",1);
	call_out("check",6+random(5),who,0);
	return 1;  
}
int check(object who,int k)
{
	if( !who )	
		return 0;
	if(base_name(environment(who)) != "/d/33tian/wuxing")
	{
		message_vision(HIY"$N�뿪�����пռ䣬�����жϡ�\n"NOR,who);
		who->delete_temp("wuxing_learning");
		who->delete_temp("wuxing_learn");
		return 0;
	}
	k = k + 1;
	if( k == 1 )	message_vision(HIY"$N�����:�������������ԣ������С�\n"NOR,who);
	if( k == 2 )	message_vision(HIY"$N�����:��ν�����ߣ���ľˮ������������֮�������ֻ����ܣ���ɴ�ǧ���硣\n"NOR,who);
	if( k == 3 )	message_vision(HIY"$N�����:����ش󷨣�����������֮��������֮�������������֮˵��\n"NOR,who);
	if( k == 4 )	message_vision(HIY"$N�����:��˼����ľ��ľ����������ˮ��ˮ�˻𡢻�˽�\n"NOR,who);
	if( k == 5 )	message_vision(HIY"$N�����:����������ˮ��ˮ��ľ��ľ���𡢻�������������\n"NOR,who);
	if( k == 6 )	message_vision(HIY"$N�����:��������ħ���ض��ݴ�������ˡ��˴���Ҳ��\n"NOR,who);
	if( k == 7 )	message_vision(HIY"$N�����:�������һ��ˮ����ˮ���̺����������ɿ�ˮ��ˮ��ɿ�����\n"NOR,who);
	if( k == 8 )	message_vision(HIY"$N�����:�����������֮�ۣ������󽣶������и���֮��������ˣ����������������໯Ҳ��\n"NOR,who);
	if( k == 9 )	message_vision(HIY"$N�����:��н��֮�������Էй�ˮ��Ȼ��н��֮�����ܷн���а���ǻ𲻿ɿ�ˮ���Ʋ����ӡ�\n"NOR,who);
	if( k == 10 )	message_vision(HIY"$N�����:ˮ��������ڱ˴�֮�ƣ��Ʋ�������������������ʱ���κΣ�\n"NOR,who);
	if( k == 11 )	message_vision(HIY"$N�����:Ω�б仯�ӡ���ǿ��֮�𣬵�����֮ˮ������ˮ��\n"NOR,who);
	if( k == 12 )	message_vision(HIY"$N�����:�Ե���֮ˮ����У���ֲ��������ܻ���Ϊ����֮��������Կ�ˮ��\n"NOR,who);
	if( k == 13 )	message_vision(HIY"$N�����:������֮�𣬵�ǿ��֮ˮ����ر��ˡ������ܻ���Ϊ����֮ˮ�������������\n"NOR,who);
	if( k == 14 )	message_vision(HIY"$N�����:��������������ԣ���ǿ���������С�ľ��֮�����ȫ�޽�ˮ�������ԣ����������\n"NOR,who);
	if( k == 15 )	message_vision(HIY"$N�����:��������������ʱ���ڱ仯֮�У�������Բ׺�Ϊɣ��Ҳ��\n"NOR,who);
	if( k == 16 )	message_vision(HIY"$N�����:�����໯������������������ĳ�������֮�������ԣ������仯��˳Ӧʱ��Ҳ��\n"NOR,who);
	if( k == 17 )	message_vision(HIY"$N�����:�������ѣ����޼�ǿ֮��������������֮���飬��Ȼ�޷��������Ϲ����������б仯�ߣ��������˶��ѡ�\n"NOR,who);
	if( k == 18 )	message_vision(HIY"$N�����:�������໯������������֮�⡣����֮��ľˮ�����������Ϊ���㡯�������������䡯�������������ݡ�Ҳ��\n"NOR,who);
	if( k == 19 )	message_vision(HIY"$N�����:�����㡢�������仯�����𡢰��������������Ϊ����֮������Ϊ����֮�ɡ�\n"NOR,who);
	if( !who->query("wuxing_known") && k > 4 )
	{
		message_vision(HIY"$Nڤڤ�У���������\n"NOR,who);
		if( random(who->query("int")) > 20 - random( who->query("lunhui_zhuanshi") ) )
			call_out("finish",6+random(5),who);
		else
			call_out("finish2",6+random(5),who);
		remove_call_out("check");	
		return 1;
	}
	if( who->query("wuxing_known") == 1 && k > 12 )
	{
		message_vision(HIY"$Nڤڤ�У���������\n"NOR,who);
		if( random(who->query("int")) > 25 - random( who->query("lunhui_zhuanshi") ) )
			call_out("finish",6+random(5),who);
		else
			call_out("finish2",6+random(5),who);
		remove_call_out("check");	
		return 1;
	}
	if( who->query("wuxing_known") == 2 && k > 18 )
	{
		message_vision(HIY"$Nڤڤ�У���������\n"NOR,who);
		if( random(who->query("int")) > 30 - random( who->query("lunhui_zhuanshi") ) )
			call_out("finish",6+random(5),who);
		else
			call_out("finish2",6+random(5),who);
		remove_call_out("check");	
		return 1;
	}
	call_out("check",6+random(5),who,k);
}

int finish(object who)
{
	object downroom = load_object(__DIR__"dadian");
	if(base_name(environment(who)) != "/d/33tian/wuxing")
	{
		message_vision(HIY"$N�뿪�����пռ䣬�����жϡ�\n"NOR,who);
		who->delete_temp("wuxing_learning");
		who->delete_temp("wuxing_learn");
		return 0;
	}
	if( !who->query("wuxing_known") )
	{
		message_vision(HIY"$N������������ܹ��������У������֮�����У������°빦����\n"NOR,who);
		message_vision(HIY"$N���Ծ���ת��Ԫ�񹦣�����֮��Ӧ�������\n"NOR,who);
		message_vision(HIY"ֻ����ͬ���ԵĹ�â���ϴ�$N����ɢ������������ӦԪ���໥��Ӧ��\n"NOR,who);
		message_vision(HIY"ʱ���������ţ�$N�����е���ʶ�𽥼��\n"NOR,who);
		message_vision(HIY"$Nһ����Х�����Ϲ�â��ʢ����ɫ��â��$N��Χ��������\n"NOR,who);
		message_vision(HIY"����һ���ɫ��â������$N�������壬$N΢΢һЦ��ʧȥ����Ӱ��\n"NOR,who);
		who->set("wuxing_known",1);
		who->delete_temp("wuxing_learn");
     		who->delete_temp("wuxing_learning");
		who->move("/d/33tian/dadian");
		message_vision(HIY"һ��ҫ�۵���Ӱ��ͻȻ�����ڴ��֮�ϣ�\n"NOR,downroom);
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��̫���Ͼ�(taishang laojun)��" + who->name() + "��������Ŭ���������������еĻ�������ѧ����"+HIB"[̫������]"+HIC"��\n\n\n"NOR,users());
		return 1;
	}
	if( who->query("wuxing_known") == 1 )
	{
		message_vision(HIY"$N��������������Զ�������֮�������������У����Ա������֮������������\n"NOR,who);
		message_vision(HIY"$N���Ծ���ת�����ķ�����Ӧ��������Ԫ�أ�\n"NOR,who);
		message_vision(HIY"$N�����Ž���������Ԫ���������ڣ�������������֮��˳����ת��������֮����\n"NOR,who);
		message_vision(HIY"ֻ��$N�����Ԫ�غ����Ϸ���ҫ�۵İ׹⣡\n"NOR,who);
		message_vision(HIW"$N�����Ԫ�غ����Ϸ���ҫ�۵İ׹⣡\n"NOR,who);
		message_vision(BLK"$N��ת�ķ�������Ľ�Ԫ�أ�ת��Ϊ���ڽ�֮���������ķ��������뱾��ˮ֮���У�˲��$N����ˮ֮�����������Ϲ�âתΪ������\n"NOR,who);
		message_vision(HIC"$N����ת�ķ��������������������ľ֮����$N������â��ʢ��\n"NOR,who);
		message_vision(HIR"$N����ת�ķ���������������������֮����$N���Ϻ�â��ʢ��\n"NOR,who);
		message_vision(HIY"$Nһ����Х����������ɽ�ӳ�һȭ������ɽ�еĽ�Ԫ�ؾ�Ȼ��$N��һȭ�ڻ��˲��٣�\n"NOR,who);
		message_vision(HIY"$N΢΢һЦ��ʧȥ����Ӱ��\n"NOR,who);
		who->set("wuxing_known",2);
		who->delete_temp("wuxing_learn");
     		who->delete_temp("wuxing_learning");
		who->move("/d/33tian/dadian");
		message_vision(HIY"һ��ҫ�۵���Ӱ��ͻȻ�����ڴ��֮�ϣ�\n"NOR,downroom);
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��̫���Ͼ�(taishang laojun)��" + who->name() + "��������Ŭ�����������������໯�ĵ���"+HIB"[̫������]"+HIC"����������˲��٣�\n\n\n"NOR,users());
		return 1;
	}
	if( who->query("wuxing_known") == 2 )
	{
		message_vision(HIY"$N�������̫�������ǣ������������������̫������������\n"NOR,who);
		message_vision(HIY"$N�����������֮���̺��������������Ȼ��̫���ܲ��ɷ֡�\n"NOR,who);
		message_vision(HIY"$N�������̫���˱�Դ֮������Ȼ�޼᲻�ݣ����ǽ����к�һ������\n"NOR,who);
		message_vision(HIY"$N���Ծ���ת�����ķ���������Ϊ��¯�����Ž����к�һ��\n"NOR,who);
		message_vision(HIY"$N�Ա�����֮���������������У�\n"NOR,who);
		message_vision(HIY"�������������༤�����������ֻ��������������������澭������\n"NOR,who);
		message_vision(HIY"������������������Ρ����������ɶ��뾲��\n"NOR,who);
		message_vision(HIY"��һ˲�䣬ԭ����Ҫ��ֹ������������ͬʱ����$N���������أ�\n"NOR,who);
		message_vision(HIY"$N������������һ�����磬�ᴩ�����������ؼ�ĺ�Ȼ����������������\n"NOR,who);
		message_vision(HIY"$N�ٿ���ǰ���д�ɽ��ֻ��һ˿һ�������֮����ϣ�\n"NOR,who);
		message_vision(HIY"$N�������ģ�ȴ�־���̫��֮���ƺ�����һ���̺���\n"NOR,who);
		message_vision(HIY"$N���ں�Ȼ����ͻȻ����һ��������$N˲��ʧȥ����Ӱ��\n"NOR,who);
		who->set("wuxing_known",3);
		who->delete_temp("wuxing_learn");
     		who->delete_temp("wuxing_learning");
		who->move("/d/33tian/dadian");
		message_vision(HIY"һ��ҫ�۵���Ӱ��ͻȻ�����ڴ��֮�ϣ�\n"NOR,downroom);
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��̫���Ͼ�(taishang laojun)��" + who->name() + "��������Ŭ���������������к�һ��������ȫ������"+HIB"[̫������]"+HIC"��\n\n\n"NOR,users());
		return 1;
	}
	return 1;	
}

int finish2(object who)
{
	object downroom = load_object(__DIR__"dadian");
	if(base_name(environment(who)) != "/d/33tian/wuxing")
	{
		message_vision(HIY"$N�뿪�����пռ䣬�����жϡ�\n"NOR,who);
		who->delete_temp("wuxing_learning");
		who->delete_temp("wuxing_learn");
		return 0;
	}
	message_vision(HIY"$N��ת��Ԫ�񹦣���Ӧ��������Ԫ�أ�\n"NOR,who);
	message_vision(HIY"ֻ����ͬ���ԵĹ�â���ϴ�$N����ɢ������������ӦԪ���໥��Ӧ��\n"NOR,who);
	message_vision(HIY"ʱ���������ţ�$N�����е���ʶ�𽥼��\n"NOR,who);
	message_vision(HIY"ͻȻ$N�ֳ�ʹ����ɫ������$N�޷��������������������߻���ħ�ˣ�\n"NOR,who);
	message_vision(HIY"���пռ�������̫���Ͼ���̾Ϣ֮����\n"NOR,who);
	message_vision(HIY"$N��ǰ����һ�����뿪�����пռ䡣\n"NOR,who);
	who->set("wuxing_cant",1);
	who->delete_temp("wuxing_learn");
     	who->delete_temp("wuxing_learning");
     	if( !who->query("wuxing_known") )
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��̫���Ͼ�(taishang laojun)��" + who->name() + "��Ե�������޷�������������ղ���ѧ��"+HIB"[̫������]"+HIC"�����ǿ�ϧ����\n\n\n"NOR,users());
	else
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��̫���Ͼ�(taishang laojun)��" + who->name() + "��Ե�������޷������������֮���ղ�����ȫ����"+HIB"[̫������]"+HIC"�����ǿ�ϧ����\n\n\n"NOR,users());
	message_vision(HIY"һ��ҫ�۵���Ӱ��ͻȻ�����ڴ��֮�ϣ�\n"NOR,downroom);
	who->move("/d/33tian/dadian");
	who->unconcious();
	return 1;	
}