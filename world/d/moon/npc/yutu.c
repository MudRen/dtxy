
#include <ansi.h>

inherit NPC;

void create() {
  set_name("����",({"yu tu","tu","rabbit"}));
  set("long","һֻ���ÿɰ���С���ã����۾��������죬��ֻ���䳤������\n");
  set("gender","Ů��");
  set("age",10);
  set("per",999);
  set("str",30+random(10));
  set("cor",40);
  set("cps",30);
  set("max_sen",1000);
  set("sen",1000);
  set("max_kee",2000);
  set("kee",2000);
  set("max_mana",500);

  set("combat_exp", 300);
  set("daoxing",300);
  set_skill("unarmed", 10);
  set_skill("baihua-zhang", 10);
  map_skill("unarmed", "baihua-zhang");
  set_skill("dodge", 20);
  
  set("limbs", ({
               "ͷ��", "����", "�ؿ�", "����", "β��","����",
               "��צ", "��צ", "����", "С��", "ǰ��", "����",
               "ǰצ", "��צ" }) );

  setup();
  carry_object("/d/moon/obj/daoyaochu")->wield();
  set("chat_chance",3);
  set("chat_chance_combat", 4);
  set("chat_msg_combat", ({
        (CYN"����Խ��Խ���ˣ����������������棬���棡�ٴ��ٴ򣡡�\n"NOR),
      }) );
}
