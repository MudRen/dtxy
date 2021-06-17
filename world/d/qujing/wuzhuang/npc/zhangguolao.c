// zhangguolao.c...weiqi, 98.02.24.
#include <ansi.h>
int fly_sea();
void qi_maolu();
inherit NPC;
void create()
{
	set_name("�Ź���", ({"zhang guolao", "zhang", "guolao"}));
	//set("title", "");
	set("gender", "����" );
	set("age", 50);
	set("per", 20);
	set("long", "һλЦ�����Ļ�����ͷ��\n");
	set("class", "xian");
	set("combat_exp", 120000);
  set("daoxing", 500000);

	set("attitude", "peaceful");
	create_family("��ׯ��", 3, "����");
	set_skill("unarmed", 60);
	set_skill("wuxing-quan", 60);
	set_skill("dodge", 80);
	set_skill("baguazhen", 70);
	set_skill("parry", 80);
	set_skill("hammer", 90);
	set_skill("kaishan-chui", 100);
	set_skill("force", 70);   
	set_skill("zhenyuan-force", 70);
	set_skill("literate", 50);
	set_skill("spells", 80);
	set_skill("taiyi", 80);
	map_skill("spells", "taiyi");
	map_skill("force", "zhenyuan-force");
	map_skill("unarmed", "wuxing-quan");
	map_skill("hammer", "kaishan-chui");
	map_skill("dodge", "baguazhen");

	set("max_kee", 500);
	set("max_sen", 500);
	set("force", 1000);
	set("max_force", 800);
	set("mana", 1600);
	set("max_mana", 800);	
	set("force_factor", 40);
	set("mana_factor", 40);

	set("maolu", 0);

	setup();
	carry_object("/d/obj/cloth/linen")->wear();
	carry_object("/d/obj/cloth/pobuxie")->wear();
	carry_object("/d/obj/weapon/hammer/jiuhulu")->wield();
}

void init()
{       
	object ob=this_player();
	object me=this_object();

	::init();

	set("chat_chance", 10);
	set("inquiry", ([
	    "���ζ���": (: fly_sea :),
		"name" : "�Ǻǣ��Ź�����Ҳ��\n",
		"here" : "��������ˣ����汻���ʵ��ˡ�\n",
	 ]) );

	set("chat_msg", ({
		"�Ź�����������Ц�˼�����\n",	
		"�Ź�������ƺ�«�ֹ���һ�ڣ�������������졣\n",
		"�Ź��ϴ��˸���ָ���������ҵ�Сë¿����������\n",
		(: random_move :)
	}) );

	if( query("maolu") == 0 )
	{
                  //call_out("qi_maolu", 1);
                    //qi_maolu();
		set("maolu", 1);
	}

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
	"�𻨾�",
	"����ɽ���",
	"���ز�",
	"�����",
	"����������",
	"���",
	});  
   	string jname;
	object me,ob;
    me=this_player();
	ob=this_object();

	  if( me->query_temp("wzg_baxian")!="go" )
		  return 0;
      if (me->query("wzggive/zhangguolao"))
    	{
	 		  message_vision(WHT"\n�Ź����ʵ�����"+CYN""+me->query("wzggive/zhangguolao")+WHT"�����������𣿣�\n"NOR,me);
			  return 1;
		}
	  if( me->query_temp("wzg/zhangguolao")!="give")
	    {
	      jname = jnames[random(sizeof(jnames))];
		  message_vision(WHT"\n�Ź�������������˵�������ǰ���һֱ��������һ�ζ���������" + RANK_D->query_respect(me) + "˵�𣬲�������һ
		      ͬȥ��ֻ����ͷ��������ر���ȵ�"+CYN""+jname+WHT"��\n"NOR,me);
		  me->set("wzggive/zhangguolao",jname);
		  return 1;
		}
	command("say " + RANK_D->query_respect(me) + "��ȥ�����������ɣ�������һ���ˣ�\n");
	ob->move("/d/changan/eastseashore");
    return 1;
}

int accept_object(object who, object ob)
{
	  object me = this_object();

	  if( !who->query("wzggive/zhangguolao"))
		  return 0;
	  if ((string)ob->query("liquid/name")!=who->query("wzggive/zhangguolao"))
   {
     command ("shake "+who->query("id"));
	call_out ("return_ob",1,who,ob);
    return 1;
  }
  

  message_vision(WHT"\n$N�ӹ�$n���˳������ɵ�������üͷ�����˶�˵"+who->query("wzggive/zhangguolao")+"ζ�����أ���ô�������ҵ��׾��㴼��\n"NOR,me,ob);
  who->set_temp("wzg/zhangguolao","give");
  who->delete("wzggive/zhangguolao");
  return 1;
}



void return_ob (object who, object ob)
{
  if (ob)
    command ("give "+ob->query("id")+" to "+who->query("id"));
}

void qi_maolu()
{
	object maolu;

	if (!present("xiao maolu")) {
        	maolu = new(__DIR__"xiaomaolu.c");
        	maolu->move( environment(this_object()) );
        }
	command("mount maolu");
	return;	
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
			if ( (string)ob->query("gender") == "����" ) command("say ʦ��̫�����ˡ�\n");
			else command("say ʦ��̫�����ˡ�\n");
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
		command("say �ã��úøɣ��Ź��ϲ��У�ͽ�ܿɲ��ܲ��ˡ�\n");
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
