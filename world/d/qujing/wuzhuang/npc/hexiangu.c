// hexiangu.c...weiqi, 98.02.24.
#include <ansi.h>
int fly_sea();
inherit NPC;
void create()
{
	set_name("���ɹ�", ({"he xiangu", "he", "xiangu"}));
	//set("title", "");
	set("gender", "Ů��" );
	set("age", 25);
	set("per", 20);
	set("long", "���ɹ������Ԫ����ϲ������λͬ�Ŵ��������á�\n���ɹ�ԭ������ã������ǿ��������ģ���Ͷ����ׯ��ǰ�ǵ��������ġ�������ʩ����\n");
	set("class", "xian");
	set("combat_exp", 120000);
  set("daoxing", 200000);

	set("attitude", "peaceful");
	create_family("��ׯ��", 3, "����");
	set_skill("unarmed", 60);
	set_skill("wuxing-quan", 60);
	set_skill("dodge", 80);
	set_skill("baguazhen", 80);
	set_skill("parry", 80);
	set_skill("sword", 90);
	set_skill("sanqing-jian", 100);
	set_skill("force", 70);   
	set_skill("zhenyuan-force", 70);
	set_skill("literate", 50);
	set_skill("spells", 80);
	set_skill("taiyi", 80);
	map_skill("spells", "taiyi");
	map_skill("force", "zhenyuan-force");
	map_skill("unarmed", "wuxing-quan");
	map_skill("sword", "sanqing-jian");
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
	carry_object("/d/obj/cloth/skirt")->wear();
	carry_object("/d/obj/cloth/shoes")->wear();
	carry_object("/d/obj/weapon/sword/snow_sword")->wield();
}

int fly_sea()
{
  string *jnames = ({
    "�ֺ�����",
	"���̾�",
	"�𻨾�",
	"����ɽ���",
	"���ز�",
	"�����",
	"����������",
	});  
   	string jname;
	object me,ob;
    me=this_player();
	ob=this_object();

	  if( me->query_temp("wzg_baxian")!="go" )
		  return 0;
      if (me->query("wzggive/hexiangu"))
    	{
	 		  message_vision(HIM"\n���ɹ��ʵ�����"+CYN""+me->query("wzggive/hexiangu")+HIM"�����õ����𣿣�\n"NOR,me);
			  return 1;
		}
	  if( me->query_temp("wzg/hexiangu")!="give")
	    {
	      jname = jnames[random(sizeof(jnames))];
		  message_vision(HIM"\n���ɹ�Ƿ��ʩ�������" + RANK_D->query_respect(me) + "�ܴ���"+CYN""+jname+HIM"�����Ҳͬȥ��\n"NOR,me);
		  me->set("wzggive/hexiangu",jname);
		  return 1;
		}
	command("say " + RANK_D->query_respect(me) + "��ȥ�����������ɣ�˵����ڶ����ߵ����ǣ�\n");
	ob->move("/d/changan/eastseashore");
    return 1;
}

int accept_object(object who, object ob)
{
	  object me = this_object();

	  if( !who->query("wzggive/hexiangu"))
		  return 0;
	  if ((string)ob->query("liquid/name")!=who->query("wzggive/hexiangu"))
   {
     command ("shake "+who->query("id"));
	call_out ("return_ob",1,who,ob);
    return 1;
  }

  message_vision(HIM"\n$N�ӹ�$n�������޵�������볢����"+who->query("wzggive/hexiangu")+"�ˣ�\n"NOR,me,ob);
  who->set_temp("wzg/hexiangu","give");
  who->delete("wzggive/hexiangu");
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
			command("say �����" + RANK_D->query_rude(ob) + "�����ù�����������ǲ��\n");
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
