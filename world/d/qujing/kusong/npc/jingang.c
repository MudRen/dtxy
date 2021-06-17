//Cracked by Roath

inherit NPC;
#include <ansi.h>
void create()
{
	set_name("���", ({ "jin gang" }));
	set("long", @LONG
��ա�
LONG);
	set("gender", "����");
	set("age", 35);
	set("attitude", "peaceful");
	set("rank_info/self", "ƶɮ");
	set("family/family_name","�Ϻ�����ɽ");
	set("class", "bonze");
  set("str",40);
	set("per",100);//means no rong-mao description.
	set("max_kee", 5000);
	set("max_gin", 5000);
	set("max_sen", 5000);
	set("force", 4000);
	set("max_force", 2000);
	set("force_factor", 150);
	set("max_mana", 3000);
	set("mana", 6000);
	set("mana_factor", 151);
	set("combat_exp", 2000000);
	set("daoxing", 10000000);

	set_skill("literate", 200);
	set_skill("spells", 200);
	set_skill("buddhism", 200);
	set_skill("unarmed", 200);
	set_skill("jienan-zhi", 200);
	set_skill("dodge", 200);
	set_skill("lotusmove", 200);
	set_skill("parry", 200);
	set_skill("force", 200);
	set_skill("lotusforce", 200);
	set_skill("staff", 200);
	set_skill("lunhui-zhang", 200);
	map_skill("spells", "buddhism");
	map_skill("unarmed", "jienan-zhi");
	map_skill("dodge", "lotusmove");
	map_skill("force", "lotusforce");
	map_skill("parry", "lunhui-zhang");
	map_skill("staff", "lunhui-zhang");
	set("chat_chance_combat", 60);
	set("chat_msg_combat", ({
		(: perform_action, "unarmed", "lingxi" :),
		(: perform_action, "unarmed", "rulai" :),
	}) );

	setup();
	carry_object("/d/nanhai/obj/jiasha")->wear();
	//carry_object("/d/nanhai/obj/nine-ring")->wield();
}

void die()
{
  object who = query_temp("last_damage_from");
  if( who->query_temp("huohun/yuanshen") )  
  {
  	who->add_temp("huohun/jingang",1);
  	if( who->query_temp("huohun/jingang") == 10 && who->query_temp("huohun/yuanshen") == 6 )
  	{
  		who->delete_temp("huohun");
  		if( random(who->query("int")) > 25 - random( who->query("lunhui_zhuanshi") ) )
  		{
  			who->add("huohun_known",1);
  			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"���캢��(honghai er)��" + who->name() + "�Ƴ�������ӡ��ʹ��Ԫ���λ����"+HIR"[���]"+HIC"�����������һ����\n\n\n"NOR,users());	
  		}	
  		else
  		{
  			who->set("huohun_cant",1);
  			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"���캢��(honghai er)��" + who->name() + "�Ƴ�������ӡ��ʹ��Ԫ���λ����ϧ�޷��������"+HIR"[���]"+HIC"�����ǿ�ϧ��\n\n\n"NOR,users());	
  		}
  	}
  }
  if( who->query_temp("piaoxue1/jingang") )  
  {
  	who->add_temp("piaoxue1/kill",1);
  	if( who->query_temp("piaoxue1/kill") == 2 && who->query_temp("piaoxue1/foyin") == 1 )
  	{
  		who->delete_temp("piaoxue1");
  		if( random(who->query("int")) > 25 - random( who->query("lunhui_zhuanshi") ) )
  		{
  			who->add("piaoxue_known",1);
  			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"����ȸ����(kongque mingwang)��" + who->name() + "�Ƴ�������ӡ����������ͷԹ�ޣ�����ѧ����"+HIW"[Ʈѩ��ʽ]"+HIC"��\n\n\n"NOR,users());	
  		}	
  		else
  		{
  			who->set("piaoxue_cant",1);
  			message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"����ȸ����(kongque mingwang)��" + who->name() + "�Ƴ�������ӡ����������ͷԹ�ޣ�ȴ��Եѧ��"+HIW"[Ʈѩ��ʽ]"+HIC"�����ǿ�ϧ��\n\n\n"NOR,users());	
  		}
  	}
  }
  message("sound", "\n���һ����ͷ���ԣ���������ȥ�ˡ�����\n\n", environment());
	destruct(this_object());
}
void unconcious()
{
	die();
}