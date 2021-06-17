//modified by vikee
//2000.10

#include <ansi.h>
inherit NPC;
#include "huoyannpc2.h"

void create()
{
        set_name("ħ��", ({ "moli hai", "duowen tianwang", "hai", "tianwang" }) );
        set("gender", "����" );
	set("long",
		"ħ���Ľ�֮һ��ʹһ��������������һ�����ã����������ң�Ҳ��\n"
                "�ء�ˮ���𡢷磬������������������������ƽ�һ�㡣\n"
	);
	set("age",50);
	set("title", "��������");
	set("attitude", "heroism");
	set("str",40);
	set("int",30);
	set("max_kee",1100);
	set("kee",1100);
	set("max_sen",1100);
	set("sen",1100);
	set("combat_exp",1000000);
        set("daoxing",1200000);
	set("force",2500);
	set("max_force",1500);
	set("mana",2500);
	set("max_mana",1600);
	set("force_factor", 80);
	set("mana_factor",80);
	
        set("eff_dx", 450000);
        set("nkgain", 500);

	set_skill("unarmed",150);
	set_skill("yingzhaogong", 150);
	set_skill("parry",150);
	set_skill("dodge",150);
	set_skill("stick",150);
	set_skill("kusang-bang",150);
	set_skill("force",150);
	set_skill("spells", 150);
	set_skill("moshenbu", 150);
	map_skill("dodge", "moshenbu");
	map_skill("parry", "bawang-qiang");
	map_skill("spear","bawang-qiang");
	map_skill("unarmed", "yingzhaogong");
	set("inquiry", ([
		"name" : "���¶�������ħ�񺣣���ʥ�Ͱ��������š�",
		"here" : "�������������, ���ھ�������ˡ�",
	]) );

	setup();
	carry_object("/d/sea/obj/dragonstick")->wield();
	carry_object("/d/obj/armor/jinjia")->wear();
}

void hurting(object me, object ob)
{
   int n;

   remove_call_out("hurting");
   if(!me->is_fighting())return;
   n = ob->query("combat_exp")/ (me->query("combat_exp")+1);
   n += ob->query("daoheng")/ (me->query("daoheng")+1);
   if(n < 2) n = 2;
   if( me->is_busy() ) {
      call_out("hurting",9+random(6),me,ob);
      return;
   }
   message_vision(HIB"$N�ͳ��������ã�����ս������Ȼ�Եõĵ���������\n"NOR,me);
   if(!random(1+n)){
      message_vision(HIB"���$N���Ե����ߵ���ȫ�������ã�\n"NOR,ob);
      ob->start_busy(2 + 60/ (ob->query_kar()+1));
      me->start_busy(60/ (me->query_kar()+1));
   }
   else{
      message_vision("$N������ţ���Ϊ������\n",ob);
   me->start_busy(2);
   }
   call_out("hurting",9+random(6),me,ob);
   return;
}

