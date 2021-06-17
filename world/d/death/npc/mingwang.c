//tomcat
//mingwang.c
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string ask_jingtian();
void create()
{
  set_name("ڤ��", ({"ming wang", "wang"}));
  set("long", "�����ǵز���������ʦ�֣���ز����Ʋ��������򲻷���ͥ�������ϳ��ظ��������ڹ��Źظ����ε���\n");
  set("title",CYN"��ڤ֮��"NOR);
  set("gender", "����");
  set("class", "youling");
  set("age", 80);
  set("attitude", "friendly");
  set("shen_type", 1);
  set("per", 30);
  set("str", 60);
  set("int", 30+random(5));
  set("max_kee", 10000);
  set("max_sen", 10000);
  set("kee", 10000);
  set("sen", 10000);

  set("force", 12000);
  set("max_force", 6000);
  set("force_factor", 300);
  set("max_mana", 5000);
  set("mana", 10000);
  set("mana_factor", 300);

  set("combat_exp", 60000000);
  set("daoxing",10000000);

   set_skill("unarmed", 300);
   set_skill("whip", 300);
   set_skill("hellfire-whip", 300);
   set_skill("dodge", 300);
   set_skill("parry", 300);
   set_skill("literate", 300);
   set_skill("spells", 300);
   set_skill("force", 300);
   set_skill("tonsillit", 300);
   set_skill("ghost-steps", 300);
   set_skill("gouhunshu", 300);
   set_skill("jinghun-zhang", 300);
   set_skill("kusang-bang", 300);
   set_skill("zhuihun-sword", 300);
   set_skill("sword", 300);
   set_skill("stick", 300);

  map_skill("force", "tonsillit");
  map_skill("unarmed", "jinghun-zhang");
  map_skill("dodge", "ghost-steps");
  map_skill("spells", "gouhunshu");
  map_skill("parry", "hellfire-whip");
  map_skill("whip", "hellfire-whip");
  map_skill("sword", "zhuihun-sword");
  set("inquiry",([
      "������ʽ": (: ask_jingtian :),
      ]));
  set("jingtian_known",3);
        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "sword","yanluo" :),
		(: perform_action, "sword","jingtian" :),
                (: exert_function, "recover" :),
                (: cast_spell, "gouhun" :),
        }) );
 
  set_temp("apply/armor", 500);
  set_temp("apply/damage", 250);
  
  create_family("���޵ظ�", 1, "��ʦ");
  setup();
  carry_object("/d/obj/cloth/baipao")->wear();
  carry_object("/d/obj/weapon/sword/qingfeng")->wield();
}

 
void attempt_apprentice(object ob)
{
     object me;
     
      ob->this_player();
   
   if( (int)ob->query("family/generation")==2 )  
  {
        command("say ���ǵزص�ͽ�ܣ�����������!");
        message_vision ("$n���һ��Ҫɱ��$N��\n",me,ob);
        kill_ob(ob);
        return ;
   }   

    if (ob->query("obstacle/number") < 26) {
        command("say ��λ" + RANK_D->query_respect(ob) + "�㻹���ȳ�ȥ����һ���ɣ�\n");
        command("sigh");
        return;
        }

    if (((int)ob->query("daoxing") < 1000000 )) {
      command("say " + RANK_D->query_rude(ob) + "�������è�İ�ʽ��ô��ù��ز�������ȥ������!");
      return;
    }
    command("grin");
    command("say �ܺã�" + RANK_D->query_respect(ob) +
       "���Ŭ�������հ��ұ���ɱ�˵ز��������ƥ��\n");
    command("recruit " + ob->query("id") );
    return;
  }

int recruit_apprentice(object ob)
{
  if( ::recruit_apprentice(ob) )
       ob->set("title", HBBLU"���Ĺ�ʥ"NOR);
    ob->set("class", "youling");
}

string ask_jingtian()
{
	object me = this_player();
	object downroom = load_object(__DIR__"wuxing");
	if( !wizardp(me) && me->query("family/family_name") != "���޵ظ�" )	
		return ("�㲻����ڤ���࣬�޷�ѧϰ������ʽ��");
	if( me->query("betray/count") )
		return ("�����Ķ����޷���ᾪ���ѧ��\n");
	if( me->query("jingtian_known") > 2 )
		return ("�⾪����ʽ�㶼ѧ���ˣ������Ҫ�����Լ����ˣ�");
	if( me->query("jingtian_cant") )
		return ("��ѧ���㶼ѧ���ˣ�����ѧ�ģ���Ҳ��᲻�ˣ�ĪҪǿ��");
	if( me->query("family/master_id") == "dizang pusa" )  
	        return ("���ǵزص�ͽ�ܣ���");
	if( me->query_temp("jingtian/dizang") )
		return ("��������ȥ�ɵ��زص��𣿣�");
	if( me->query_temp("jingtian/jiejie") )
		return ("��������ȥ�ƻ������ŹصĽ���𣿣�");
	if( !me->query("jingtian_known"))
	{
		if( me->query_skill("literate",1) < 200 )
			return ("�������ѧʶ��������������ѧ��");
		if( me->query_skill("zhuihun-sword",1) < 200 )
			return ("��Ľ���̫���ˣ�");
		if( me->query_skill("tonsillit",1) < 200 )
			return ("���ڹ�̫���ˣ�");
		me->set_temp("jingtian/dizang",1);
		command("say �ã���Ȼ�г�Ϣ��");
		command("say ���Ȱ��Ұѵزظɵ���");
		command("say �ҵظ������ɼң������ظ��ڳ�ӯ�ų�Թ��޵���Ϣ��");
		command("say �������ܹ�������Щ��Ϣ�����ܴ����ǿ�Լ���ʵ����");
	}
	if(me->query("jingtian_known")==1)
	{
		if( me->query_skill("literate",1) < 250 )
			return ("Ҫ������ľ����ѧ�������ѧʶ��������");
		if( me->query_skill("zhuihun-sword",1) < 250 )
			return ("��Ľ���̫���ˣ�");
		if( me->query_skill("tonsillit",1) < 250 )
			return ("���ڹ�̫���ˣ�");
		me->set_temp("jingtian/jiejie",1);
		command("say �ã���Ȼ�г�Ϣ��ɱ�˵زس�����һ�ڶ�����");
		command("say �������Ź��ǵ���ǽʵ������ͥ���������ֲ��µĽ�硣");
		command("say ���������˾�����ʽ�Ժ󣬵ز����Ѳ����ҵĶ��֣��������ǲ��������취��");
		command("say ����Ұ��ǽ����(break)�ˣ��Դ��Ժ�ڤ��������ҵ������ˡ�");
	}
	if(me->query("jingtian_known")==2)
	{
		if( me->query_skill("literate",1) < 300 )
			return ("Ҫ������ľ����ѧ�������ѧʶ��������");
		if( me->query_skill("zhuihun-sword",1) < 300 )
			return ("��Ľ���̫���ˣ�");
		if( me->query_skill("tonsillit",1) < 300 )
			return ("���ڹ�̫���ˣ�");
		me->set_temp("jingtian/lingwu",1);
		command("say �ã���Ȼ�г�Ϣ������ڤ��ʵ��ǿ���������������Ҳ������û�취�ˡ�");
		command("haha");
		command("say ��ظ��о����κ����ϵ�Թ�����أ���ȥ��������(xiulian)�ɡ�");
		command("say �����Ҿ������κ�������ȫ�����˾�����ʽ�ġ�");
		command("say ϣ�������������ѧ��ҲΪ��ڤ��ͳһ����������ס�");
	}
	return ("���к�Ϸ���ˣ��ٺ٣�");
}