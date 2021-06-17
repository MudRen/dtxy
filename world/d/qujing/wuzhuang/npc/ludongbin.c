
// ludongbin.c...weiqi, 98.02.24.
#include <ansi.h>
int fly_sea();
string give_book();
string ask_jinguzhou();

inherit NPC;
void create()
{
	set_name("������", ({"lu dongbin", "lu", "dongbin"}));
	//set("title", "������");
	set("gender", "����" );
	set("age", 35);
	set("per", 30);
	set("long", "�������������Ԫ����������ĵ����ˣ��Ĳɷ�����ɫ�����졣\n");
	set("class", "xian");
	set("combat_exp", 120000);
  set("daoxing", 800000);

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
	set_skill("literate", 120);
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

	set("inquiry", ([
		"name" : "��ׯ�۴�������Ҳ��\n",
		"here" : "���ںδ����������ӡ�\n",
   	    "���ζ���": (: fly_sea :),
    	"rumors": (: ask_jinguzhou :),
		"�ĵ�" : (: give_book :),		 
		"�����ĵ�" : (: give_book :),
	]) );

	set("no_book", 0);

	setup();
	carry_object("/d/obj/cloth/xianpao")->wear();
	carry_object("/d/obj/weapon/sword/changjian")->wield();
}
int fly_sea()
{
    string jname;
	object me,ob;
    me=this_player();
	ob=this_object();

	  if( me->query_temp("wzg_baxian")!="go" )
		  return 0;
      if (me->query("wzggive/ludongbin"))
    	{
	 		  message_vision(HIY"\n������̾����������"+HIR""+me->query("wzggive/ludongbin")+HIY"�ͺ��ˣ�\n"NOR,me);
			  return 1;
		}
	  if( me->query_temp("wzg/ludongbin")!="give")
	    {
	      jname="�����";
		  message_vision(HIY"\n��������̾����" + RANK_D->query_respect(me) + "����������ǿ����Ԫ����Ϣ���ң���Ȼ������ԣ�
	      ֻ�н���"+HIR""+jname+HIY"֮�������ص�������Ҫ��������������
              ��Ȼ����һͬǰȥ�������棡\n"NOR,me);
		  me->set("wzggive/ludongbin",jname);
		  return 1;
		}
	command("say " + RANK_D->query_respect(me) + "��ȥ�����������ɣ�˵��Ҳͬȥ��\n");
	ob->move("/d/changan/eastseashore");
    return 1;
}

int accept_object(object who, object ob)
{
	  object me = this_object();

	  if( !who->query("wzggive/ludongbin"))
		  return 0;
	  if ((string)ob->query("liquid/name")!=who->query("wzggive/ludongbin"))
   {
     command ("shake "+who->query("id"));
	call_out ("return_ob",1,who,ob);
    return 1;
  }
  
  if (ob->query("liquid/remaining") == 0)
  {
    message_vision (HIY"$Nҡ��һ��ͷ��˵�����յ�,����ƭ����?\n"NOR,me);
    call_out ("return_ob",1,ob,who);
    return 1;
  }
  message_vision(HIY"\n$N�ӹ�$n"+HIY"��ʩһ�����$N�ָܻ����Ѹ�٣�ȫ��" + RANK_D->query_respect(who) + "��ʱ����"+HIR""+who->query("wzggive/ludongbin")+HIY"������Ͷ���ȥ�����ɣ�\n"NOR,me,ob);
  who->set_temp("wzg/ludongbin","give");
  who->delete("wzggive/ludongbin");
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
			command("say �����" + RANK_D->query_rude(ob) + "��������Ҳ������ǲ���\n");
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

string give_book()
{
	object me = this_player();

	if( query("no_book") == 0 )
	{
		carry_object("/d/obj/book/chunyang");
		command("give xinde to " + me->query("id"));
		set("no_book", 1);
		return "������˵�����ã���Ȼ�������ˣ����Ҿ͸���ɡ�\n";
	}
	else
	{
		return "������˵����̫�����ˣ����Ѿ������ˡ�\n";
	}

}

string ask_jinguzhou()
{
	if (this_player() -> query_temp("aware_of_jinguzhou")) 
		return "��������˵������ô�����ʣ�\n";
	this_player() -> set_temp("aware_of_jinguzhou", 1);
	command("whisper " + this_player() -> query("id") 
		+ " ��˵������������������͵Ľ����䡣");
	return "��Ե�ߵ�֮����Ե����֮���Ϳ����ĸ����ˡ�\n";
}
�