//tomcat
//nuwa.c
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
   set_name("����", ({"li dan", "li", "laojun"}));
   set("title", HIW"̫���Ͼ�"NOR);
   set("gender", "����" );
   set("age", 180);
//   set("per", 24);
//   set("str", 30);
   set("long", "���������������������ε����������ݺ���޵��£�����һ�������壡\n");
   set("class", "xian");
//   set("combat_exp", 5600000);
   set("attitude", "peaceful");
   create_family("��ׯ��", 1, "��ʦ");
   set("rank_info/respect", "�Ͼ�");
   set_skill("unarmed", 300);
   set_skill("wuxing-quan", 300);
   set_skill("dodge", 300);
   set_skill("baguazhen", 300);
   set_skill("parry", 300);
   set_skill("sword", 300);
   set_skill("sanqing-jian", 300);
   set_skill("staff", 300);
   set_skill("fumo-zhang", 300);
   set_skill("hammer", 300);
   set_skill("kaishan-chui", 300);
   set_skill("blade", 300);
   set_skill("yange-blade", 300);
   set_skill("force", 300);   
   set_skill("zhenyuan-force", 300);
   set_skill("literate", 300);
   set_skill("spells", 300);
   set_skill("taiyi", 300);
   map_skill("spells", "taiyi");
   map_skill("force", "zhenyuan-force");
   map_skill("unarmed", "wuxing-quan");
   map_skill("sword", "sanqing-jian");
   map_skill("dodge", "baguazhen");
   map_skill("staff", "fumo-zhang");
   map_skill("blade", "yange-blade");
   map_skill("hammer", "kaishan-chui");

  set("str",100);
  set("per",100);
  set("max_kee", 10000);
  set("max_gin", 10000);
  set("max_sen", 10000);
  set("force", 10000);
  set("max_force", 10000);
  set("force_factor", 500);
  set("max_mana", 10000);
  set("mana", 10000);
  set("mana_factor", 500);
  set("combat_exp", 4000000);
  set("daoxing", 10000000);

   set("spell_qiankun_on", 1); //to use cast qiankun, must set this.
   set("chat_chance_combat", 90);
   set("chat_msg_combat", 
   ({
     (: cast_spell, "zhenhuo" :),
     (: cast_spell, "qiankun" :),
   }) );
       setup();
       carry_object("/d/obj/cloth/baguapao")->wear();
       carry_object("/d/obj/weapon/sword/qinghong")->wield();
       
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
   if( (int)ob->query_skill("taiyi", 1) < 180 ) {
	command("say ��λ" + RANK_D->query_respect(ob) + "��̫���ɷ���ỹ�������������Ҳ����Ϊ���ѣ�\n");
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
}



