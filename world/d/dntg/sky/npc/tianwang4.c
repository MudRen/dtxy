//created by vikee
//2000.10

#include <ansi.h>
inherit NPC;
#include "huoyannpc2.h"
void create()
{
        set_name("ħ����", ({ "moli shou", "chiguo tianwang", "shou", "tianwang", "wang" }) );
        set("gender", "����" );
        set("long","
�Ĵ�����֮һ�����ű����󹬰�ȫ���ص�����ͬС�ɡ���
���书�ƺ�������һ�ɣ������������������ɱ�־��У���
û����֪����ʲô��Ҳ������Ϊ��ˣ���ʲŷ�����������
���Ρ�\n"
        );
	set("class", "xian");
	set("title", "�ֹ�����");
        set("age",43);
        set("str",30);
        set("int",37);
        set("max_kee",1200);
        set("kee",1100);
        set("max_sen",1100);
        set("sen",1100);
        set("combat_exp",2000000);
        set("daoxing",1500000);
        set("force",2500);
        set("max_force",1500);
        set("mana",2500);
        set("max_mana",1500);
        set("force_factor", 70);
        set("mana_factor",80);

        set("eff_dx", 450000);
        set("nkgain", 450);

        set_skill("unarmed",200);
	set_skill("changquan", 200);
        set_skill("parry",200);
        set_skill("dodge",200);
        set_skill("mace",200);
	set_skill("spells", 200);
        set_skill("wusi-mace",200);
        set_skill("force",200);
	set_skill("moshenbu", 200);
	map_skill("dodge", "moshenbu");
        map_skill("mace","wusi-mace");
        map_skill("parry","lunhui-zhang");
	map_skill("unarmed", "changquan");
        set("inquiry", ([
                "name" : "���¾��ǳֹ���������ʥ�Ͱ��ر����š�",
                "here" : "������Ǳ����ţ������Ǻ󹬽��ء�",
        ]) );
        setup();
	carry_object("/d/obj/fabao/biyu-pipa");
        carry_object("/d/obj/weapon/mace/copperjian")->wield();
        carry_object("/d/obj/armor/jinjia")->wear();
}
void hurting(object me, object ob)
{
   int n;
   string *parts;

   remove_call_out("hurting");
   if(environment(me)!=environment(ob) || !me->is_fighting()) return;
   if(me->is_busy() ){
      call_out("hurting",9+random(6),me,ob);
      return;
   }
   message_vision(HIW"$n������ȡ�������������ڿ��У�����һֻ���󣻿���Ѫ�裬������������$Nҧ����\n"NOR,ob,me);
   n = 2 + ob->query("daoheng")/ (me->query("daoheng")+1);
   n += ob->query("combat_exp")/ (me->query("combat_exp")+1);
  if(random(n)){
      message_vision("$N���һ�����󵨣�\n�������ŵ���æ���ħ���ٵ����С�\n",ob);
      me->start_busy(2);
   }
   else {
      parts = ob->query("limbs");
      message_vision("���$N"+parts[random(sizeof(parts))]+"��һ��ҧ��Ѫ��ģ����\n",ob);
      ob->receive_wound("kee",ob->query("max_kee")/5,me);
   }
   call_out("hurting", random(6)+9,me, ob);
}
