// By Canoe 2001-06-11
// ���ӳ���浵����
// ���ٳ���answer����
// ���ӳ谮\�޴�\����\ι�� ����
//     dote\flog\peilian\feed
//    sloth\cool\tonicity\zhongcheng
//    ���� ���侲��ǿ׳���ҳ�
// block�����Ǹ����к���,

#include <ansi.h>
inherit NPC;
inherit F_SAVE;

private string SAVE_NAME="pet_save";
private static int can_save=1;


void create()
{
      seteuid(getuid());
        set_name("����", ({"pet"}) );
           set("gender", "Ů��");
        set("race","Ұ��");
        set("age", 1);
        set("base_name","��");
        set("attitude", "friendly");
        set("long","С�һ������peilian dote feed flog\n");
        set("combat_exp", 100);
        set("daoxing",100);
        set("str",3);//����
        set("str",3);
        set("cor",3);
        set("per",3);//��ò
        set("spi",3);//����
        if(query("sloth"))
        set("cps",3+(int)query("sloth")/100);//�侲
        else set("cps",3);
        if((int)query("cool")>(int)query("sloth"))
        set("con",3+((int)query("cool")-(int)query("sloth"))/100);//����
        else set("con",3);
        if(!query("zhongcheng")) set("zhongcheng",100);// �ҳ�
        set("owner","canoe");
        set("limbs", ({ "ͷ��", "����", "ǰ��", "���", "β��" }) );
          set("verbs", ({ "bite", "claw" }) );
        set("ride/msg", "��");
        set("ride/dodge", 20);
        set_temp("apply/attack", 60);
        set_temp("apply/armor", 60);
        set("is_pet",1);
        setup();
}

void reset()
{
        if( !environment() || ! find_living(query("owner")) )
        {
                destruct(this_object());
                return;
        }
}
void unconcious()
{
        return die();
}
string query_save_file()
{
        string id;
        id = query("owner");
        if( !id ) return 0;
        return sprintf(DATA_DIR"pet/%c/%s", id[0], id);
}
int save()
{
        string file;
        if( stringp(file = this_object()->query_save_file()) ) {
                assure_file(file+ __SAVE_EXTENSION__);
                return save_object(file);
        }
        return 0;
}
int block(object me,object pet)
{
      if(pet->query("owner")!=me->query("id"))
          {
           write("���ﲻ��ʶ��,�±������,�����첻�����㡣\n");
           return 0;
          }
      if(me->is_busy()|| me->query_temp("pending/exercising")||me->is_fight())
           {
           write("����æ���ء�\n");
           return 0;
           }
      if(environment(me)->query("no_fight")  ||
      	 environment(me)->query("no_magic") )
      	   {
      	   write("��ȫ����ֹ��Ū���\n");
      	   return 0;
      	   }
      else return 1;
}
int restore()
{
        string file;

        if( stringp(file = this_object()->query_save_file()) )
                return restore_object(file);
        return 0;
}
void die()
{
        int i;
        object owner, *enemy;
        int gin,kee,sen,exp;

        exp = (int) query("combat_exp");
        gin = (int) query("max_gin");
        kee = (int) query("max_kee");
        sen = (int) query("max_sen");
        if(!environment()->query("no_death_penalty"))
        set("combat_exp",exp/10 * 9);
        set("eff_kee",kee);
        set("eff_gin",gin);
        set("eff_sen",sen);
        set("kee",kee);
        set("gin",gin);
        set("sen",sen);
        save();
        ::die();
}
void init()
{
        add_action("do_kill",({"kill","fight","steal"}));
        add_action("do_mount","mount");
        add_action("do_gongji","gongji");//������ȥ���� ok
        add_action("do_teach","teach");// �����ﴫ���书  ok
        add_action("do_shape","shape");// �鿴����  ok
        add_action("do_dote","dote");// �谮pet  ok
        add_action("do_flog","flog");// �޴�pet  ok
        add_action("do_cundang","cundang");// ����save ok
        add_action("do_feed","feed");// ι��pet ok
        add_action("do_peilian","peilian");// ���� ok
}

int do_mount(string arg)
{
     object me=this_object(),who=this_player(),env;
     if(!arg) return 0;
     env = environment(who);
     if(present(arg,env)!=me) return 0;
     if(me->query("owner")==who->query("id"))
     {
     who->set_temp("pet",1);
     return 0;
     }
     message_vision("$n���������$N�۵���ͷ��Ҳû����ȥ��\n",who,me);
     return 1;
}
int do_kill(string arg)
{
        object me,who;
        string name,verb,what,obj;
        if (!arg) return 0;
        verb=query_verb();
        me=this_player();

        if(verb=="steal") {
          if(sscanf(arg, "%s from %s", what, obj)!=2 )
            return 0;
          }
        else obj=arg;

        if(!objectp(who=present(obj,environment(me)))
           || !living(who)) return 0;

        if(who==this_object()) {
          switch(verb) {
            case "kill":
              tell_object(environment(this_object()),
                who->query("name")+"ƴ���ؿ������������ˣ�"+
                me->query("name")+"Ҫɱ�ң����������ѽ��\n");
              break;
            case "fight":

              tell_object(environment(this_object()),
                who->query("name")+"�������������ˣ�"+
                me->query("name")+"Ҫ���ҵ��ǳԣ����������ѽ��\n");
              break;
            case "steal":

              tell_object(environment(this_object()),
                who->query("name")+"�������������ˣ�"+
                me->query("name")+"Ҫ͵���ҵ��ǣ�\n");
              break;
          }
        }
        command(verb);
        return 0;
}
void relay_emote(object ob, string verb)
{
        if( !userp(ob) ) return;

        switch(verb) {
        case "kick":
                command("say ���ˡ��������ˡ�����"  + ob->query("name") + "����Ү��");
                command("kick " + ob->query("id"));
                        break;
        case "slap":
                command("say ���ˡ��������ˡ�����"  + ob->query("name") +
"����Ү����ʹ����������");
                command("slap " + ob->query("id"));
                        break;
        case "hit":
                command("pain " + ob->query("id"));
                        break;
        case "bite":
                command("face " + ob->query("id"));
                        break;
        case "papaya":
                command("pout");
                        break;
                }
}
void relay_whisper(object me, string msg)
{
        if (me->query("id")!=query("owner"))
        {
                message_vision((string)this_object()->query("name")
                        + "�ɻ�ؿ���$N��\n", me);
                return;
        }
        if( strsrch(msg, "chat") != -1 ||
            strsrch(msg, "sldh") != -1 ||
            strsrch(msg, "es") != -1 ||
            strsrch(msg, "rumor") != -1 ||
            strsrch(msg, "xyj") != -1 ||
            strsrch(msg, "tell") != -1 ||
            strsrch(msg, "follow") != -1 ||
            strsrch(msg, "apprentice") != -1 ||
            strsrch(msg, "answer") != -1 ||
            strsrch(msg, "recruit") != -1 )
                return;
        if (msg)
        {
                remove_call_out ("relaying");
                call_out ("relaying", 1+random(3), msg);
        }
}
void relaying (string msg)
{
        command (msg);
}
int do_teach(string arg)
{
         object me,who;
        int gin_cost,amount;
        int myskill, itskill;
        me = this_player();
          who = this_object();
        if(!myskill = me->query_skill(arg,1))
        return notify_fail("���������󻹲����أ�\n");
        if(arg != "unarmed" && arg != "parry" && arg != "dodge")
        return notify_fail("��ѧ��������ܵģ�\n");
          if(who->query("owner")==me->query("id")) {
        itskill = query_skill(arg,1);
        if(myskill <= itskill)
        return notify_fail(name()+"�Գ�Ц��Ŀ�������㡣\n");
        if((int)me->query("potential")-(int)me->query("learned_points") < 1)
        return notify_fail("���Ǳ�ܲ�����\n");
        gin_cost = 100/ (int)me->query_int();
        if((int)me->query("gin") < gin_cost)
        return notify_fail("����Ȼ̫����û�а취�̣�\n");
        me->receive_damage("gin",gin_cost);
        me->add("potential",-1);
        amount = (int)me->query_int() * (int)me->query_int()/100;
        message_vision(sprintf("$N�����䷳�ؽ�$n��%s����\n",to_chinese(arg)),me,this_object());

        improve_skill(arg,amount);
        message_vision(sprintf("$N�ƺ����ѧ����һЩ��%s����\n",to_chinese(arg)),this_object());
          }
        return 1;
}
string status_color(int current, int max)
{
        int percent;

        if( max>0 ) percent = current * 100 / max;
        else percent = 100;
        if( percent > 100 ) return HIC;
        if( percent >= 90 ) return HIG;
        if( percent >= 60 ) return HIY;
        if( percent >= 30 ) return YEL;
        if( percent >= 10 ) return HIR;
        return RED;
}
int do_shape(string arg)
{
          object me,who;
          me = this_player();
          who = this_object();
          if(who->query("owner")==me->query("id"))
           {       mapping my;
        string shape;
        float at_pt,pa_pt,do_pt;
        my = query_entire_dbase();
        if((int)query("tonicity")>(int)query("sloth"))
        set("str",3+((int)query("tonicity")-(int)query("sloth"))/100);//����
        if((int)query("zhongcheng")>(int)query("sloth"))
        set("cor",3+((int)query("zhongcheng")-(int)query("sloth"))/100);//����
        set("ride/dodge", 20+(int)query_skill("dodge",1)/2);
        set_temp("apply/attack", 60+query("tonicity")/100);
        set_temp("apply/armor", 60+query("cool")/100);
        printf("����%s%3d/ %3d %s(%3d%%)"NOR"  ����%s%3d/ %3d %s(%3d%%)"NOR"  ��%s%3d/ %3d %s(%3d%%)\n"+NOR,
                status_color(my["gin"], my["eff_gin"]), my["gin"],my["eff_gin"],
                status_color(my["eff_gin"], my["max_gin"]),     my["eff_gin"] * 100 / my["max_gin"],
                status_color(my["kee"], my["eff_kee"]), my["kee"], my["eff_kee"],
                status_color(my["eff_kee"], my["max_kee"]),     my["eff_kee"] * 100 / my["max_kee"],
                status_color(my["sen"], my["eff_sen"]), my["sen"], my["eff_sen"],
                status_color(my["eff_sen"], my["max_sen"]),     my["eff_sen"] * 100 / my["max_sen"]
        );
        printf("���ˣ� %s\t���飺 %d\t���У� %d\n",
        my["owner"], my["combat_exp"],my["daoxing"]
        );
        printf("������ %d\t��ʶ�� %d\t������ %d\t���ǣ� %d\n",
        query_str(), query_cor(),query_cps(),query_con(),
        );
        printf("�侲�� %d\tǿ׳�� %d\t���裺 %d\t�ҳϣ� %d\n",
        query("cool"),query("tonicity"), query("sloth"),query("zhongcheng"),
        );
        at_pt= COMBAT_D->skill_power(this_object(), "unarmed", 1)/100;
        pa_pt= COMBAT_D->skill_power(this_object(), "unarmed", 2);
        do_pt= COMBAT_D->skill_power(this_object(), "dodge", 2);
        printf("�������� %s �������� %s ���ӹ����� %d\t���ӷ����� %d\n\n",
        "" + (at_pt+1), "" + (pa_pt/2+do_pt/2+1),query_temp("apply/attack"),query_temp("apply/armor")
        );
        printf("/cmds/usr/skillspet"->pet_skill(this_object()));
          }
        return 1;
}
int do_cundang()
{
        object pet,me;
        pet=this_object();
	me=this_player();
	if(pet->query("owner")==me->query("id"))
	 {
        	if(pet->save()) message_vision("$N�浵�ɹ�!\n",pet);
        	else message_vision("$N�浵ʧ��!\n",pet);
         }
        else write(HIW"��������ĳ���?\n"NOR);
        return 1;
}

int do_feed()
{
       object me;
       //object feeob;
       int petskill;
       object pet = this_object();
       me = this_player();
        //if ( !arg || !(feeob=present(arg, me)) )
        //   return notify_fail("��Ҫ����ιʲô�ԣ�\n");
        //else if (arg != "grass")
        //   return notify_fail("�ⶫ������Բ��ˡ�\n");
      if(block(me,pet))
        {
                if (me->query("kee")>50)  me->add("kee",-50);
                else
                   {
                   message_vision("$Nѵ�����ȣ����ｻ�ᣬ���ˡ�\n", me,pet);
                   me->unconcious();
                   return 1;
                   }
         //       destruct(feeob);
                message_vision("$N��$nι��һЩʳ�$n�����ζ�ĳ���������\n", me,pet);
                me->start_busy(random(2)+1);
                if ( random(5) != 0 )
                {
                pet->add("zhongcheng",random(5)+1);
                message_vision("$n���ǵؿ���$N,$n���ҳ϶�������.\n",me,pet);
                       if(random(50)==0)
                       {
                       petskill=pet->query_skill("dodge",1);
                       petskill-=1;
                       if (petskill<0) petskill=0;
                       pet->set_skill("dodge",petskill);
                       message_vision("$N��̫��������ˡ�\n",pet);
                       }
                }
                else
                  {
                  pet->add("zhongcheng",-random(10));
                  if(pet->query("zhongcheng")<0) pet->set("zhongcheng",0);
                  message_vision("$n���˻�����,��������.�����ؿ���$N��\n",me,pet);
                  }
       }
      return 1;
}

int do_dote()
{
       object me;
       object pet = this_object();
       me = this_player();
       if(block(me,pet))
        {
                if (me->query("kee")>50)  me->add("kee",-50);
                else
                   {
                   message_vision("$Nѵ�����ȣ����ｻ�ᣬ���ˡ�\n", me,pet);
                   me->unconcious();
                   return 1;
                   }
                message_vision("$N�谮��������$n��ͷ��ǣ����ɢ����\n", me,pet);
                me->start_busy(random(2)+1);
                if ( random(5) != 0 )
                {
                pet->add("zhongcheng",random(20)+1);
                message_vision("$n���ǵؿ���$N,$n���ҳ϶������ˡ�\n",me,pet);
                       if(random(50)==0)
                       {
                       if(pet->query("zhongcheng")>49) pet->add("zhongcheng",-50);
                       else pet->set("zhongcheng",0);
                       message_vision("$N���鲻�ã��������ˡ�\n",pet);
                       }
                }
                else
                  {
                  pet->add("sloth",random(10));
                  message_vision("$n�����ˡ�\n",me,pet);
                  }
       }
      return 1;
}

int do_flog()
{
       object me;
       object pet = this_object();
       me = this_player();
       if(block(me,pet))
        {
                if(random(pet->query("zhongcheng"))<20)
                   {
                   me->star_busy(2);
                   message_vision("$n�ƺ���̫��$N�Ļ��ˡ�\n", me,pet);
                   return 1;
                   }

                if (me->query("kee")>100)  me->add("kee",-100);
                else
                   {
                   message_vision("$Nѵ�����ȣ����ｻ�ᣬ���ˡ�\n", me,pet);
                   me->unconcious();
                   return 1;
                   }
                message_vision("$N���ϵؿ���$n�����б��Ӻ�������ر޴�$n��\n", me,pet);
                me->start_busy(random(2)+1);
                if ( random(5) != 0 )
                {
                pet->add("cool",random(15)+1);
                pet->add("zhongcheng",-1);
                pet->add("combat_exp",random(10)+1);
                message_vision("$n��������Ų�������������������ˡ�\n",me,pet);
                       if(random(50)==0)
                       {
                       if(pet->query("zhongcheng")>49) pet->add("zhongcheng",-50);
                       else pet->set("zhongcheng",0);
                       message_vision("$N��������ˣ������ʧ����\n",pet);
                       }
                }
                else
                  {
                  pet->add("cool",-random(10));
                  message_vision("$nѵ�����ȣ�����״��Ƿ���ˡ�\n",me,pet);
                  }
       }
      return 1;
}

int do_peilian()
{
       object me;
       object pet = this_object();
       me = this_player();
       if(block(me,pet))
        {
               if(random(pet->query("zhongcheng"))<20)
                   {
                   me->star_busy(2);
                   message_vision("$n�ƺ���̫��$N�Ļ��ˡ�\n", me,pet);
                   return 1;
                   }
               if (me->query("kee")>200)  me->add("kee",-200);
                else
                   {
                   message_vision("$Nѵ�����ȣ����ｻ�ᣬ���ˡ�\n", me,pet);
                   me->unconcious();
                   return 1;
                   }
                message_vision("$N��$n����ѵ���������Ժ�$nһ��������\n", me,pet);
                me->start_busy(random(2)+1);
                if ( random(5) != 0 )
                {
                pet->add("tonicity",random(15)+1);
                pet->add("sloth",random(3));
                pet->add("daoxing",random(10)+1);
                message_vision("$n����ѵ��������ǿ׳�ˡ�\n",me,pet);
                       if(random(50)==0)
                       {
                       if(pet->query("zhongcheng")>49) pet->add("zhongcheng",-50);
                       else pet->set("zhongcheng",0);
                       message_vision("$N�۵ð�����������ҳ϶Ƚ����ˡ�\n",pet);
                       }
                }
                else
                  {
                  pet->add("zhongcheng",-random(10));
                  message_vision("$nѵ�����ȣ���ʼ�������ˡ�\n",me,pet);
                  }
       }
      return 1;
}
