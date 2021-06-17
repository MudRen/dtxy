inherit __DIR__"yaoguai.c";
#include "/d/obj/yao/yao-xian.h"
#include <ansi.h>
// here should be this NPC specific skills.

void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;
        int exp;

        set("class","dragon");
        set("family/family_name","��������");
        me->set("title",HIC"�޾��粨"NOR);
        me->set_skill("unarmed", j);
        me->set_skill("dodge", j);
        me->set_skill("parry", j);
        me->set_skill("force", j);
        me->set_skill("spells", j);
 
        me->set_skill("fork", j+random(5));
        me->set_skill("fengbo-cha", j+random(5));
        me->set_skill("hammer",j+random(5));
        me->set_skill("huntian-hammer",j+random(5));
        me->set_skill("dragonstep", j+random(5));
        me->set_skill("dragonfight", j+random(5));
        me->set_skill("dragonforce", j+random(5));
        me->set_skill("seashentong", j+random(5));

        me->map_skill("force", "dragonforce");
        me->map_skill("fork", "fengbo-cha");
        me->map_skill("hammer","huntian-hammer");
        me->map_skill("parry", "huntian-hammer");
        me->map_skill("spells", "seashentong");
        me->map_skill("dodge", "dragonstep");
        me->map_skill("unarmed", "dragonfight");

	exp=me->query("combat_exp");
        set("chat_chance_combat", cast_chance(level));
        set("chat_msg_combat", ({
            (: cast_spell, "freez" :),
            (: perform_action, "unarmed","sheshen" :),
	  }) );
	carry_object("/d/obj/cloth/shoupiqun.c")->wear();
}
