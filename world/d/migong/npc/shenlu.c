#include <ansi.h>

inherit __DIR__"beast.c";

void create()
{
  set_name(HIW"��ɫ��¹"NOR, ({"jiuse shenlu", "shenlu"}));
  set("race", "Ұ��");
  set("age", 100);
  set("long", "һͷ���Ǿ�ɫ÷��¹���������ƺ��з��ƹ���\n");
  set("daoxing", 1500000);

  set("combat_exp", 300000);
  set("limbs", ({ "ͷ��", "����", "ǰ��", "���", "β��" }) );
  set("verbs", ({ "bite"}));

  set("max_kee", 3000);
  set("kee", 3000);
  set("max_sen", 3000);
  set("sen", 3000);

  set_skill("dodge", 200);
  set_skill("parry", 200);
  set_skill("unarmed", 200);

  set("ride/need_train", 1);
  set("ride/msg", "��");
  set("ride/dodge", 80);

  set_temp("apply/dodge", 100);
  set_temp("apply/attack",100);
  set_temp("apply/armor", 100);

  setup();
}





  
