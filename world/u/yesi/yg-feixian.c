
// ��������
//lestat 2001

inherit __DIR__"guai.c";
#include <ansi.h>

void set_skills(int max_value, int level)
{
        int guai_value;
        ::set_skills(max_value, level);
        
       	if (level==1) guai_value = max_value+max_value/8;
	else if (level==2) guai_value = max_value+max_value/6;
	else guai_value = max_value+max_value/4;
        set_skill("unarmed", guai_value+random(16));
        set_skill("dodge", guai_value+random(16));
        set_skill("parry", guai_value+random(16));
        set_skill("force", guai_value+random(16));
        set_skill("spells", guai_value+random(16));
 
        set_skill("mace", guai_value+random(16));
        set_skill("dashen-bian", guai_value+random(16));
        set_skill("sword",guai_value+random(16));
        set_skill("wugou-jian",guai_value+random(16));
        set_skill("lingyunbu", guai_value+random(16));
        set_skill("yuxu-spells", guai_value+random(16));
        set_skill("kaitian-zhang", guai_value+random(16));
        set_skill("xuanzong-force", guai_value+random(16));

        map_skill("force", "xuanzong-force");
        map_skill("sword", "wugou-jian");
        map_skill("mace","dashen-bian");
        map_skill("parry", "wugou-jian");
        map_skill("spells", "yuxu-spells");
        map_skill("dodge", "lingyunbu");
        map_skill("unarmed", "kaitian-zhang");
        create_family("����ɽ���鶴",2 , "����");
	set("title",HIW"�������"NOR);
        set("chat_chance_combat", 70);
        set("chat_msg_combat", ({
        (: perform_action,"sword", "feixian" :),
        (: perform_action,"sword", "fengshen" :),
        }) );
        carry_object("/d/obj/weapon/sword/qinghong.c")->wield();
        carry_object("/d/obj/cloth/shoupiqun.c")->wear();
}

