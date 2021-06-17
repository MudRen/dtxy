inherit NPC;
#include <ansi.h>
void leave();
void leave2();

void create()
{
        set_name("�����ػ���", ({ "binghun guard", "guard" }) );
        set("age", 2000);
        set("class", "yao");
        set("long", 
"����ǽ����������ħ�����֣�ͨ�����������˱�ѩ��������\n");
        
        set("str", 48);
        set("cor", 52);
        set("cps", 22);

        set("max_kee", 15000);
        set("max_mana",2000);
        set("mana",2000);
        set("max_sen", 6000);
        set("attitude", "heroism");

        set("combat_exp", 2000000+random(2000000));
        
        set_temp("apply/attack", 100);
        set_temp("apply/damage",100);
        set_temp("apply/armor", 500);
	set("family/family_name","��ѩɽ");
        setup();
}


void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;
        me->set_skill("dodge", j+random(15));
        me->set_skill("parry", j+random(15));
        me->set_skill("force", j+random(15));
        me->set_skill("blade", j+random(15)); 
        me->set_skill("sword", j+random(15)); 
        me->set_skill("spells",j+random(15));
        me->set_skill("unarmed", j+random(15));        
        
        me->set_skill("bainiao-jian", j+random(15));
        me->set_skill("bingpo-blade", j+random(15));
        me->set_skill("dengxian-dafa", j+random(15));
        me->set_skill("cuixin-zhang", j+random(15));
        me->set_skill("ningxie-force", j+random(15)); 
        me->set_skill("xiaoyaoyou", j+random(15)); 

        me->map_skill("force", "ningxie-force");
        me->map_skill("blade", "bingpo-blade");        
        me->map_skill("parry", "bainiao-jian");
        me->map_skill("spells", "dengxian-dafa");
        me->map_skill("dodge", "xiaoyaoyou");
        me->map_skill("unarmed", "cuixin-zhang");
        me->map_skill("sword", "bainiao-jian");
        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
        	(: perform_action, "blade", "baoxue" :),
		(: exert_function, "ningxie" :),
        }) );
	carry_object("/d/obj/weapon/blade/iceblade")->wield();
        carry_object("/d/obj/cloth/shoupiqun")->wear();
}

void copy_status(object me,object ob, int lv)
{
        int j, lvl,k,m;
        object qm=new("/d/changan/npc/qianmian.c");
	int base=20;

	lvl=lv+base-2;

        if(qm) {
            mapping skill=ob->query_skills();
            int i=sizeof(skill);
            int *level, max_level;
	    int max_sen, max_kee;

	    if(i>0) {
		level=values(skill);
		max_level=level[0];
		while(i--) { // find out victim's maximum level
		    if(level[i]>max_level)
			max_level=level[i];
		}
	        max_level=max_level*lvl/base;

	    } else max_level=1;

	    qm->copy_status(this_object(), ob, lvl);
            destruct(qm);

	    k=(query("daoxing")+query("combat_exp"))/2;
	    for(m=1;m<300;m=m+10) {
		if(m*m*m/10>k) break;
	    }
	    m=m*lvl/base/3;
	    if(max_level<m) max_level=m;

	    // skill level will be set to the maximum level
	    // of the player.
	    set_skills(max_level, lv);
	    set("owner",ob);
	    max_sen=query("max_sen")/4;
	    max_kee=query("max_kee")/4;
	    add("eff_sen",max_sen);
	    add("eff_kee",max_kee);
	    add("sen",max_sen);
	    add("kee",max_kee);
	    add("max_sen",max_sen);
	    add("max_kee",max_kee);

	} else { // sth goes wrong.
	    leave();
	    return;
	}

	  add("force",query("force")); // double force.
	                               // because players have fabao.
	                             // mana is doubled when copying.
        set("force_factor", query_skill("force")/2);
        set("mana_factor", query("max_mana")/30+1);
	
	set("daoxing",(query("daoxing")*2+query("combat_exp"))/3);
}

void unconcious()
{
 	die();
}
void die()
{
	if( query("kee") > 1 && query("sen") > 1 )
	{
		message_vision(HIR "\n\nһ�ɳ���������ҽ����������ע��$N���ڣ�\n\n" NOR,this_object());
		set("eff_kee",query("max_kee"));
		set("kee",query("max_kee"));
		set("eff_sen",query("max_sen"));
		set("sen",query("max_sen"));
		set("force",query("max_force")*2);
		set("mana",query("max_mana")*2);
		return ;
	}
	::die();
}

void leave()
{
      if(this_object()) { 
        if(environment())
          message("vision",HIB + name() + 
		  "����һ�Σ����һ������ɢȥ�ˡ�\n" NOR,environment());
	this_object()->move("/obj/empty");
	call_out("leave2",5);
      }
      return;
}

void leave2()
{
    if(this_object()) {
	destruct(this_object());
    }
}

void heart_beat() {      
   if (!query_temp("ningxie") && is_fighting())
      command("perform ningxie");
      ::heart_beat();
}