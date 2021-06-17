inherit NPC;
#include <ansi.h>
void leave();
void leave2();
void create()
{
	set_name("ħ��", ({ "mo shou", "mo" }));
	set("family/family_name","���ƶ�");
	set("age", 500+random(80));
	set("class", "yao");
	set("combat_exp", 3000);
	set("attitude", "heroism");
	set_skill("unarmed", 10);
	set_skill("jinghun-zhang", 10);
	map_skill("unarmed", "jinghun-zhang");
	set_skill("dodge", 10);
	set_skill("ghost-steps", 10);
	map_skill("dodge", "ghost-steps");
	set("str", 48);
        set("cor", 52);
        set("cps", 22);

        set("max_kee", 15000);
        set("max_mana",2000);
        set("mana",2000);
        set("max_sen", 6000);

        set("combat_exp", 2000000+random(2000000));
        
        set_temp("apply/attack", 150);
        setup();
}

void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;
        me->set_skill("unarmed", j);
        me->set_skill("dodge", j);
        me->set_skill("parry", j);
        me->set_skill("force", j);
        me->set_skill("spells", j);
        me->set_skill("spear",j); 
        
        me->set_skill("wuyue-spear", j+random(15));
	me->set_skill("huoyun-qiang", j+random(15));        
        me->set_skill("spells",j+random(15));
        me->set_skill("moshenbu",j+random(15));
        me->set_skill("pingtian-dafa", j+random(15));
        me->set_skill("unarmed", j+random(15));        
        me->set_skill("moyun-shou", j+random(15));
        me->set_skill("huomoforce", j+random(15)); 

        me->map_skill("force", "huomoforce");
        me->map_skill("spear", "wuyue-spear");        
        me->map_skill("parry", "wuyue-spear");
        me->map_skill("spells", "pingtian-dafa");
        me->map_skill("dodge", "moshenbu");
        me->map_skill("unarmed", "moyun-shou");
        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
        	(: perform_action, "spear", "buhui" :),
		(: perform_action, "spear", "fengchan" :),
        }) );
	carry_object("/d/obj/weapon/spear/huaji")->wield();
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