//tomcat
//nuwa.c
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
       set_name("Ů�����",({"nu wa","niangniang"}));
       set("long", "��ò��������������ɫ���ˣ���Ȼ���﹬�����ٷ�\n");
       set("title", HIC"������Ů"NOR);
       set("gender", "Ů��");
       set("age", 30);
       set("str", 1000);
       set("class", "xian");
       set("attitude", "friendly");
       set("rank_info/respect", "����");
       set("per", 30);
	set("int", 30);
       set("max_kee", 4000);
       set("max_gin", 4000);
       set("max_sen", 4000);
       set("kee", 4000);
       set("gin", 4000);
       set("sen", 4000);
       set("force", 16000);
       set("max_force", 8000);
       set("force_factor", 300);
       set("max_mana", 8000);
       set("mana", 16000);
       set("mana_factor", 300);
       set("combat_exp", 10000000);
       set("daoxing", 8000000);
       set("eff_dx", 100000);
       set("combat_exp", 2000000);
       set_skill("literate", 300);
       set_skill("unarmed", 300);
       set_skill("dodge", 300);
       set_skill("force", 300);
       set_skill("parry", 300);
set_skill("blade", 300);
       set_skill("sword", 300);
       set_skill("spells", 300);
       set_skill("moonshentong", 300);
       set_skill("xuanhu-blade", 300);
       set_skill("baihua-zhang", 300);
       set_skill("moonforce", 300);
       set_skill("snowsword", 300);
       set_skill("moondance", 300);
       set_skill("whip", 300);
       map_skill("spells", "moonshentong");
       map_skill("unarmed", "baihua-zhang");
       map_skill("force", "moonforce");
       map_skill("sword", "snowsword");
       map_skill("parry", "snowsword");
       map_skill("dodge", "moondance");

       create_family("�¹�", 1, "����");
       set("chat_chance_combat", 90);
       set("chat_msg_combat", ({
                (: cast_spell, "mihun" :),
                (: cast_spell, "arrow" :),
                (: cast_spell, "shiyue":),
                (: perform_action, "sword", "wuxue" :),
                (: perform_action, "sword", "tian" :),
          }) );
       setup();
       carry_object("/d/moon/obj/luoyi")->wear();
       carry_object("/d/moon/obj/feijian")->wield();
       
}

void attempt_apprentice(object ob)
{
   
   ob=this_player();
   if(ob->query("obstacle/number") < 26) {
	command("say ��λ" + RANK_D->query_respect(ob) + "�ҵ���ȡ�������ĺ���Ϣ��\n");
	command("addoil");
	return;
	}	
   if ((int)ob->query("daoxing") < 1000000 ) {
  	command("shake");
 	command("say ����в������\n");
	return;
      }
   if( (int)ob->query_skill("moonshentong", 1) < 180 ) {
	command("say ��λ" + RANK_D->query_respect(ob) + "���¹��ɷ���ỹ�������������Ҳ����Ϊ���ѣ�\n");
	command("sigh");
	return;
	}   
   
     command("pat "+ob->query("id"));
     command("say ��Ȼ" + RANK_D->query_respect(ob)+ "��ˣ��Ҿ��������ˡ�\n");
        command("recruit " + ob->query("id") );
        return ;
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "xian");
     ob->set("title", HBBLU"�㺮��Ů洴���"NOR);
}


