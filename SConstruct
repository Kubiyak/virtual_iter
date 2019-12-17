optimized_env = Environment(CXX="g++-8", CXXFLAGS="--std=c++17 -O2")
optimized_env.VariantDir("build/optimized", "./")
optimized = optimized_env.Program('build/optimized/virtual_iter_test',
                                 ['build/optimized/compile_virtual_iter.cpp'], LIBS=['pthread'])
Depends('build/optimized/virtual_iter_test', ['virtual_iter.h', 'virtual_std_iter.h'])
optimized_env.Alias('optimized', optimized)

