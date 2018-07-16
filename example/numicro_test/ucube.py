src     = Split('''
        numicro_test.c
''')

component = aos_component('numicro_test', src)
component.add_comp_deps('kernel/yloop', 'tools/cli')
component.add_global_macros('AOS_NO_WIFI')
