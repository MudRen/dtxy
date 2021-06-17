//lestat,2001
#include <ansi.h>
inherit NPC;

string *names = ({
  "��ʯ���þ�",
  "��ͷ������",
  "��ɽ����",
  "��β���꾫",
  "����ʥĸ",
  "����ʥĸ",
  "ʯ�����",
});
void create()
{
   string str;
   set_name(HIB+names[random(sizeof(names))]+NOR, ({"lao yao", "lao", "yao"}));
   set("long", "��ɽ��������õ���������\n");
//   set("title", HIR"ʳ����"NOR);
   set("race", "Ұ��");
   set("age", 100+random(201));
   set("combat_exp", 5000000+random(500001));
   set("daoxing", 5000000+random(500001));
   set("limbs", ({ "ͷ��", "����", "ǰצ", "β��", "��Ƥ", "��צ"}) );
   set("verbs", ({ "bite", "claw"}) );
   set("attitude", "aggressive");
   set("per", 10);
   set("bdt", 1);
   set("max_kee", 6000);
   set("kee", 6000);
   set("sen", 6000);
   set("max_sen", 6000);
   set("force", 2000);
   set("mana", 8000);
   set("max_mana", 8000);
   set("max_force", 2000);
   set("force_factor", 75);
   set("mana_factor", 75);
   set_skill("parry", 200);
   set_skill("unarmed", 200);
   set_skill("dodge", 200);
   set_skill("blade", 200);
   set("chat_chance", 10);
        set("chat_msg", ({
                (: random_move :),
        }) );
   add_temp("apply/damage", 50);
   setup();
   carry_object("/d/obj/cloth/shoupiqun")->wear();
   carry_object("/d/qujing/jilei/obj/armor")->wear();
   carry_object( __DIR__ "lingzhi");
   	add_money("silver", random(50));

}
/*
int heal_up()
{
	if( environment() && !is_fighting() ) {
		call_out("leave", 1);
		return 1;
	}
	return ::heal_up() + 1;
}

void leave()
{
	object owner;
	message("vision",
		 name() + "˵��������ȥ�Ѵ��ƻʵ�ɱ�ˣ�\n\n"
		+ name() + "����ھ���һ���粻���ˡ�\n" , environment(),
		this_object() );
	destruct(this_object());
}*/
void init( )
{
	object ob;	
        remove_call_out("hunting");
	if( interactive(ob = this_player())  ) {
        call_out("hunting",1);
        }
	if(!environment()->query("no_fight") && random(10) < 5)
        call_out("hunting",1);
}

void hunting()
{
	int i;
        object *ob;
        ob = all_inventory(environment());
        for(i=sizeof(ob)-1; i>=0; i--) {
        if( !ob[i]->is_character() || ob[i]==this_object() || !living(ob[i])) continue;
        if(ob[i]->query("vendetta/authority")) continue;
                kill_ob(ob[i]);
                ob[i]->fight(this_object());
        }
}

void die()
{
        object ob, me, corpse;
        
        ob = this_object();
        me = query_temp("last_damage_from");
        
        message_vision(WHT"$N���һ��,�����Ҳ!!���ض�����\n"NOR,ob,me);
        if( objectp(corpse = CHAR_D->make_corpse(this_object())) )
        corpse->move(environment(this_object()));
        if(!me) { destruct(ob); return; }
        else{
        if((int)me->query("combat_exp") < 10000000)   {//�е�����
        message("vision", me->name() + "ɱ��ʳ������,��Ϊ������������\n", me);
        me->add("combat_exp",1000);
        me->add("potential",1000);
        destruct(ob);
        }
        message("vision", me->name() + "��Ϊ�����ˡ�\n", me);
//        me->add("score",2);
//        me->add("shen",10);
        destruct(ob);
        return;
             }
}

