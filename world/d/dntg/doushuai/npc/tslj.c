//created by vikee
//2000.10

 
inherit NPC;

void create()
{
  set_name("̫���Ͼ�", ({"taishang laojun", "laojun"}));
  set("gender", "����");
  set("age", 50);
  set("per", 25);
  set("long", "���ʹ��￴�ذ���¯�ĵ�ʿ��\n");
  set("attitude", "friendly");
  set("max_kee", 200);
  set("max_gin", 200);
  set("max_sen", 200);
  set("force", 200);
  set("max_force", 200);
  set("mana", 200);
  set("max_mana", 200);
  set("combat_exp", 5000);
  set("force_factor", 5);
  set_skill("unarmed", 10);
  set_skill("dodge", 10);
  set_skill("parry", 10);
  setup();
  carry_object("/d/lingtai/obj/cloth.c")->wear();
}



