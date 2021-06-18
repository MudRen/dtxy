//2001 by lestat
// go.c
// #pragma save_binary
#include <ansi.h>
inherit F_CLEAN_UP;
#include "/cmds/std/valid_move.h";

mapping default_dirs = ([
	"north":		"��",
	"south":		"��",
	"east":			"��",
	"west":			"��",
	"northup":		"����",
	"southup":		"�ϱ�",
	"eastup":		"����",
	"westup":		"����",
	"northdown":	"����",
	"southdown":	"�ϱ�",
	"eastdown":		"����",
	"westdown":		"����",
	"northeast":	"����",
	"northwest":	"����",
	"southeast":	"����",
	"southwest":	"����",
	"up":			"��",
	"down":			"��",
	"enter":		"��",
	"out":			"��",
]);


mapping reverse_dir=([
	"north":		"����",
	"south":		"����",
	"east":	    	"����",
	"west":	    	"����",
	"northup":		"�ϱ�",
	"southup":		"����",
	"eastup":		"����",
	"westup":		"����",
	"northdown":	"�ϱ�",
	"southdown":	"����",
	"eastdown":		"����",
	"westdown":		"����",
	"northeast":	"���Ϸ���",
	"northwest":	"���Ϸ���",
	"southeast":	"��������",
	"southwest":	"��������",
	"up":			"����",
	"down":	    	"����",
	"enter":		"����",
	"out":	    	"����",
]);

void create() { seteuid(getuid()); }

int main(object me, string arg, int silent)
{
    	mixed dest;
	string ridemsg, mout, min, dir,msg, blk, gud, skill, face, thing_msg,dir1,str,str1;
	object env, obj, ridee, blocker, thing;
	mapping block;
	mapping exit;
	object *f_obs, *ob;
	int valid;
    int count = 0, my_dex, i,n,i_env,i_obj;
	if( !arg ) return notify_fail("��Ҫ���ĸ������ߣ�\n");

        if(!valid_move(me)) return 0;

	env = environment(me);
	if(!env) return notify_fail("������Ҳȥ���ˡ�\n");

	if( !mapp(exit = env->query("exits")) || !exit[arg] ||  undefinedp(exit[arg]) ) {
		if( query_verb()=="go")
			return notify_fail("�������û�г�·��\n");
		else
			return 0;
	}

	dest = exit[arg];
    dest = env->query("exits/"+arg);
	if (dest && objectp(dest))
	    obj = dest;
	else if( !(obj = load_object(dest)) )
	        return notify_fail("��Ҫȥ������û����ͨ��\n");
	else if( !(obj = find_object(dest)) )
		return notify_fail("�޷��ƶ���\n");

	valid=(int)env->valid_leave(me, arg);
	if( !valid ) return 0;
	if(valid>1) return 1;

	if( !undefinedp(default_dirs[arg]) )
		dir = default_dirs[arg];
	else
		dir = arg;

        if (ridee = me->ride())
          ridemsg = ridee->query("ride/msg")+"��"+ridee->name()+"̤��һ������";
        else
          ridemsg = "";

        if(ridee && !valid_move(ridee))
           return notify_fail("��������߶����ˡ�\n");

if(me->is_ghost()&&domain_file(base_name(environment(me)))!="death")
 {
 	        write(BLU"ͻȻ�������������������һ��ն�������ɭ������:������Ӵ������Ӵ!��\n"NOR);
		write(HIW"һ�������������������ֻص��˹��Ź�\n"NOR);
                me->move("/d/death/gate");
                return 1;
 }

//�����ǹ��ڰ���ͺ�ҹ��ʾ������

	if( !env->valid_leave(me, arg) ) return 0;

	if( !undefinedp(default_dirs[arg]) )
		dir = default_dirs[arg];
	else
		dir = arg;
	if( !undefinedp(reverse_dir[arg]) )
		dir1="��"+reverse_dir[arg];
	else dir1="��֪��������";

	n=NATURE_D->night();
	i_env=(int)env->query("outdoors");
	i_obj=(int)obj->query("outdoors");

	if (!n) i=1;
	if (!i_env && !i_obj) i=1;
	if (n && i_env && !i_obj) i=2;
	if (n && ! i_env && i_obj) i=3;
	if (n && i_env && i_obj ) i =4;
	if( me->is_fighting() )
	{str="����ײײ�����˹�����ģ����Щ�Ǳ���\n";
	 str1="��" + dir + env->query("short") +"��Ķ����ˡ�\n";
	}else
		{str=dir1+env->query("short") +"���˹�����\n";str1="��" + dir + "�뿪��\n";}

	if (objectp(thing = me->query_temp("armor/cloth")))
			thing_msg = "����" + thing->query("name");
		else
			thing_msg = "ȫ��һ˿���ҵ�";
	        if (objectp(thing = me->query_temp("weapon")))
			thing_msg += "��ִ" + thing->query("name");
	if ( me->query("race") == "Ұ��")
		{
			mout = me->name() + "������" + dir + "һ�ܾ���ʧ�ˡ�\n";
			min = me->name() + "��" + dir + env->query("short") + "���ش��˳�������������������š�\n";
		}
		else
		{
if (ridee = me->ride())
			{
	if( ridee && ridee->query("bird") ) {
     str="����"+ridee->name()+dir1+env->query("short") +"���˹�����\n";
     str1="����"+ridee->name()+"��" + dir  + "��ȥ��\n";
	}else{

	str="����"+ridee->name()+dir1+env->query("short") +"һ·���۶�����\n";
	str1="����"+ridee->name()+"��" + dir + "���۶�ȥ��\n";
	}
	switch( i)
	{	case 1 :
		mout = me->name() + str1;
		min = me->name() + thing_msg +str;
		break;
		case 2 :
		if(me->query("gender") == "Ů��")
		{
		mout = "һ��ٻӰ" + str1;
		min =  me->name() + thing_msg + str;
		}
		else
		{
		mout = "һ����Ӱ"  +str1;
		min  = me->name() + thing_msg +str;
		}
		break;
		case 3 :
		if(me->query("gender") == "Ů��")
		{
		mout = me->name() + str1;
		min =  "һ��ٻӰ" + thing_msg + str;
		}
		else
		{
		mout = me->name() + str1;
		min  = "һ����Ӱ" + thing_msg + str;
		}
		break;
		case 4 :
			if(me->query("gender") == "Ů��")
		{
		mout = "һ��ٻӰ" + str1;
		min =  "һ��ٻӰ" + thing_msg + str;
		}
		else
		{
		mout = "һ����Ӱ" + str1;
		min  = "һ����Ӱ" + thing_msg + str;
		}
	}
		}
			else
			{

	switch( i)
	{	case 1 :
		mout = me->name() + str1;
		min = me->name() + thing_msg + str;
		break;
		case 2 :
		if(me->query("gender") == "Ů��")
		{
		mout = "һ��ٻӰ" + str1;
		min =  me->name() + thing_msg + str;
		}
		else
		{
		mout = "һ����Ӱ" + str1;
		min  = me->name() + thing_msg + str;
		}
		break;
		case 3 :
		if(me->query("gender") == "Ů��")
		{
		mout = me->name() + str1;
		min =  "һ��ٻӰ" + thing_msg + str;
		}
		else
		{
		mout = me->name() + str1;
		min  = "һ����Ӱ" + thing_msg + str;
		}
		break;
		case 4 :
			if(me->query("gender") == "Ů��")
		{
		mout = "һ��ٻӰ" + str1;
		min =  "һ��ٻӰ" + thing_msg + str;
		}
		else
		{
		mout = "һ����Ӱ" + str1;
		min  = "һ����Ӱ" + thing_msg + str;
		}
	}
		}
		}
//////////////////////�����ҹ�޶�����
		if( !wizardp(me) || !me->query("env/invisibility") )
	{
	    	if (environment(me) && environment(me)->query("no_look"))
				message( "vision", "һ��ģ����Ӱ��" +  mout, environment(me), ({me}) );
		else
	message( "vision", mout, environment(me), ({me}) );
			}
		if( (! ridee || ridee->move(obj)) && me->move(obj, silent) ) {
		me->remove_all_enemy();
		if( !wizardp(me) || !me->query("env/invisibility") ) {
	    			if (environment(me) && environment(me)->query("no_look"))
		    			message( "vision", "һ��ģ����Ӱ��" +  min, environment(me), ({me}) );
				else
		message( "vision", min, environment(me), ({me}) );
				}
		me->set_temp("pending", 0);
		if (env != obj)
			all_inventory(env)->follow_me(me, arg);
//		if (ridee)
//			tell_object (me,"��"+min);
		/////////////ɱ�˷�ͨ��
		if (userp(me) && me->query_condition("no_pk_time") &&
		me->query_temp("rumor_time")+10<time() &&
		  MISC_D->find_place(environment(me))!=
		me->query_temp("last_place"))
		{
		  me->set_temp("last_place",MISC_D->find_place(environment(me)));
		  msg="��˵�ٸ�ͨ��ɱ�˷�"+HIW+me->query("name")+HIM+"�����"+HIC+me->query_temp("last_place")+HIM+"������û��\n";
		CHANNEL_D->do_channel(this_object(),"rumor",msg);
		me->set_temp("rumor_time",time());
			}
		return 1;
	}

	return 0;
}

void do_flee(object me)
{
	mapping exits;
	string *directions;

	if( !environment(me) || !living(me) ) return;
	exits = environment(me)->query("exits");
	if( !mapp(exits) || !sizeof(exits) ) return;
	directions = keys(exits);
	if (environment(me) && environment(me)->query("no_flee")) return;
	tell_object(me, "�������һ��������ˣ�����\n");
        if( me->query_temp("no_move") ) {
          tell_object (me, "���㱻��ס�ˣ��Ӳ�����\n");
          return;
        }

	if( random(me->query_skill("dodge")/10 + me->query("kar")) < 10 ) {
	   tell_object(me, "������ʧ�ܡ�\n");
	   return;
	}

	main(me, directions[random(sizeof(directions))], 0);
}

int help(object me)
{
	write(@HELP
ָ���ʽ : go <����>

������ָ���ķ����ƶ���

HELP
    );
    return 1;
}
