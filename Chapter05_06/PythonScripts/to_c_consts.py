def to_c_consts(data, filename):
  str_out = ''

  # Write the header guard
  header_guard = filename.upper()
  str_out += '#ifndef ' + header_guard + '\n'
  str_out += '#define ' + header_guard + '\n'

  for x in data:
    value    = x[0]
    var_name = x[1]
    c_type   = x[2]
    str_out += 'const ' + c_type + ' '
    str_out += var_name + ' = '
    str_out += str(value)
    str_out += ';\n'

  str_out += '#endif\n'

  # Save the C header file
  h_filename = filename + '.h'
  open(h_filename, "w").write(str_out)