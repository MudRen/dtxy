inherit NPC;
string ask_for_leave();

void create()
{
        set_name("½ѹ", ({"luya"}));
        set("gender", "����" );
        set("age", 40);
        set("title","����ɽ���鶴�ܼ�");
        set("long", "����ɽ���鶴ɢ��½ѹ���ڶ��м��ιܼ�ְ֮��\n");
        set("combat_exp", 50000);
  set("daoxing", 500000);

        set("attitude", "peaceful");
        set("per", 35);
        set("max_kee", 500);
        set("max_gin", 500);
        set("max_sen", 500);
        set("inquiry", ([
                "����" : (: ask_for_leave :),
                "leave" : (: ask_for_leave :),
                ]) );
        setup();
        carry_object("/d/obj/cloth/linen")->wear();
        }

void init()
{
        add_action("do_agree", "agree");
}

string ask_for_leave()
{
        object me=this_player();

        if (me->query("family/family_name") == "����ɽ���鶴" ) {
                command("say �����ִ����ɽ������ȴ�м��仰˵��");
                me->set_temp("betray", 1);
                return ("����ʦ��Ҫ��Ҫ��һ���ͷ������Ը��(agree)��");
        }

        return ("���ɲ�֪��\n");
}

int do_agree(string arg)
{
        if(this_player()->query_temp("betray")) {
                message_vision("$N���������Ը�⡣\n\n", this_player());
                command("say ������ִ����ɽ�������ɽȥ�ɣ�");
                this_player()->add("betray/count", 1);
                this_player()->add("betray/kunlun", 1);
this_player()->set("combat_exp",this_player()->query("combat_exp")/5*4);
this_player()->set("daoxing",this_player()->query("daoxing")/5*4);
                if( this_player()->query_skill("yuxu-spells") )
                    this_player()->delete_skill("yuxu-spells");
                if( this_player()->query_skill("xuanzong-force") )
                    this_player()->delete_skill("xuanzong-force");

                
                this_player()->delete("family");
                this_player()->delete("class");
                this_player()->set("title", "��ͨ����");
                this_player()->set_temp("betray", 0);
                this_player()->save();
                command("say �����޳����Ի�Կ�������Ϊ֮������\n");
                return 1;
        }
}
