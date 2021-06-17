// tomcat
 
#include <ansi.h>

inherit NPC;
inherit F_MASTER;
// inherit SKILL;

void create()
{
  set_name("ף����", ({"zhurong shi", "zhurong", "shi"}));
   
  set("title", HIR"��ħ"NOR);
  set("gender", "����");
  set("age", 43);
  set("str", 45);
  set("per", 35);
  set("int", 30);
  set("cor", 50);
  set("cps", 40);
  set("combat_exp", 10000000);
  set("daoxing", 10000000);
  set_skill("spear", 300);
  set_skill("force", 300);
  set_skill("dodge", 300);
  set_skill("parry", 300);
  set_skill("unarmed", 300);
  set_skill("huoyun-qiang", 300);
  set_skill("literate", 300);
  set_skill("stick", 300);
  set_skill("dali-bang", 300);
  set_skill("spells", 300);
  set_skill("pingtian-dafa", 300);
  set_skill("moshenbu", 300);
  set_skill("huomoforce", 300);
  set_skill("moyun-shou", 300);
  map_skill("force", "huomoforce");
  map_skill("spells", "pingtian-dafa");
  map_skill("unarmed", "moyun-shou");
  map_skill("spear", "huoyun-qiang");
  map_skill("parry", "huoyun-qiang");
  map_skill("dodge", "moshenbu");
  set("max_sen", 6000);
  set("max_kee", 8000);
set("force", 10000);
set("max_force", 6000);
set("mana",2000);
set("max_mana",1000);
set("force_factor", 200);
set("force_mana", 100);
  set("chat_chance_combat", 80);
  set("chat_msg_combat", ({
		(: perform_action, "unarmed", "zhangxinlei" :),
		(: perform_action, "spear", "lihuo" :),
		(: cast_spell, "zhuang" :),
  }) );
 
  create_family("���ƶ�", 1, "��");
  setup();
 
  carry_object("d/obj/weapon/spear/huomoqiang")->wield();
  carry_object("/d/obj/armor/jinjia")->wear();
}
 
void attempt_apprentice(object ob)
{  
    
    ob=this_player();
   
   if( (string)ob->query("family/family_name")!="���ƶ�") {
        command("say  �Ҳ���ʶ�㡣\n");
       return;
      }
    
      if ((int)ob->query("daoxing") < 1000000 ) {
       command("say �����̫���ˡ�\n");
       return;
      }

  if (ob->query("obstacle/number") < 25) {
        command("say ��λ" + RANK_D->query_respect(ob) + "����Ϊʦ��Ҫ��������ȡ
�����ѣ�\n");
        command("sigh");
        return;
        }

        if( (int)ob->query_skill("huomoforce", 1) < 180 ) {
        command("say ��λ" + RANK_D->query_respect(ob) + "�����һ�ħ�Ĵ��ˣ���Ļ�ħ�ķ���������\n");
        command("sigh");
        return;
        }

  command("recruit " + ob->query("id") );
  return ;
}
int recruit_apprentice(object ob)
{
  if( ::recruit_apprentice(ob) )
    ob->set("class", "yaomo");
    ob->set("title",HBRED"����а��"NOR);
}
