// tieguaili.c...weiqi, 98.02.24.

#include <ansi.h>
inherit NPC;
int fly_sea();

void create()
{
	set_name("������", ({"tieguai li", "tieguai", "li"}));
	//set("title", "");
	set("gender", "����" );
	set("age", 42);
	set("per", 12);
	set("long", "���ŵ�һ˫�ò�Ь������һ�����û�˱�����Ŀ�����ۣ���������ߵ�С����һ��������̬��\n");
	set("class", "xian");
	set("combat_exp", 120000);
  set("daoxing", 300000);

	set("attitude", "peaceful");
	create_family("��ׯ��", 3, "����");
	set_skill("unarmed", 60);
	set_skill("wuxing-quan", 60);
	set_skill("dodge", 80);
	set_skill("baguazhen", 80);
	set_skill("parry", 80);
	set_skill("staff", 90);
	set_skill("fumo-zhang", 100);
	set_skill("force", 70);   
	set_skill("zhenyuan-force", 70);
	set_skill("literate", 20);
	set_skill("spells", 80);
	set_skill("taiyi", 80);
	map_skill("spells", "taiyi");
	map_skill("force", "zhenyuan-force");
	map_skill("unarmed", "wuxing-quan");
	map_skill("staff", "fumo-zhang");
	map_skill("dodge", "baguazhen");

	set("max_kee", 500);
	set("max_sen", 500);
	set("force", 1000);
	set("max_force", 800);
	set("mana", 1600);
	set("max_mana", 800);	
	set("force_factor", 40);
	set("mana_factor", 40);

	set("inquiry",([
    "���ζ���": (: fly_sea :),
		]));

	setup();
	carry_object("/d/obj/cloth/pobuyi")->wear();
	carry_object("/d/obj/cloth/lancaoxie")->wear();
	carry_object("/d/obj/weapon/staff/tieguai")->wield();
}

int fly_sea()
{
  string *jnames = ({
    "�Ⱦ�",
    "����Ͼ�",
    "ˮ��",
    "�ֺ�����",
    "����",
    "���׾�",
    "�ϰ׸�",
	"�׾�",
	"���̾�",
	"�ݵ��Ѿ�û��ζ�Ĳ�ˮ",
	"��ˮ",
	"���վ�",
	"����������",
	"���",
	"�𻨾�",
	"����ɽ���",
	"���ز�",
	"�����",
  });  
   	string jname;
	object me,ob;
    me=this_player();
	ob=this_object();

	  if( me->query_temp("wzg_baxian")!="go" )
		  return 0;
      if (me->query("wzggive/tieguaili"))
    	{
	 		  message_vision(HIG"\n�������ʵ�����Ҫ��"+CYN""+me->query("wzggive/tieguaili")+HIG"�����õ����𣿣�\n"NOR,me);
			  return 1;
		}
	  if( me->query_temp("wzg/tieguaili")!="give")
	    {
	      jname = jnames[random(sizeof(jnames))];
		  message_vision(HIG"\n�������۾�һ����$N˵�����ã��ã��ã�Ҫ���ٴ��ϵ�"+CYN""+jname+HIG"�͸����ˣ�\n"NOR,me);
		  me->set("wzggive/tieguaili",jname);
		  return 1;
		}
	command("say " + RANK_D->query_respect(me) + "��ȥ�����������ɣ�������һ���ˣ�\n");
	ob->move("/d/changan/eastseashore");
    return 1;
}

int accept_object(object who, object ob)
{
	  object me = this_object();

	  if( !who->query("wzggive/tieguaili"))
		  return 0;
	  if ((string)ob->query("liquid/name")!=who->query("wzggive/tieguaili"))
   {
     command ("shake "+who->query("id"));
	call_out ("return_ob",1,who,ob);
    return 1;
  }
  

  message_vision(HIG"\n$NЦ���е�����$n�����������С$nѽ�������Ҿʹ���ȥ�������森\n"NOR,me,ob);
  who->set_temp("wzg/tieguaili","give");
  who->delete("wzggive/tieguaili");
  return 1;
}



void return_ob (object who, object ob)
{
  if (ob)
    command ("give "+ob->query("id")+" to "+who->query("id"));
}

void attempt_apprentice(object ob)
{
	if( (string)ob->query("family/family_name")=="��ׯ��" )
	{
		if( (int)ob->query("family/generation") < 3  )
		{
			if ( (string)ob->query("gender") == "����" ) command("say ʦ���Ц�ˡ�\n");
			else command("say ʦ�ü�Ц�ˡ�\n");
		}
		else if( (int)ob->query("family/generation") ==3  )
		{
			command("kick " + ob->query("id") );
			command("say �����" + RANK_D->query_rude(ob) + "��������ǲ���ӣ�\n");
		}
		else 
		{
			command("consider");
			command("say �����Լ�Ҫ�ݵģ���ʦ�����������ҿɵ����㵲��\n");
			command("recruit " + ob->query("id") );
		}
	}

	else
	{
		command("say �ã�����ׯ��һ���˲ű�������ɵø�ʦ��������\n");
		command("recruit " + ob->query("id") );
	}

	return;
}

int recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
		ob->set("class", "xian");
}




�