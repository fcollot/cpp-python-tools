import sys
import code
import tkinter as tk
import rlcompleter as rl

class TKConsole(tk.Text):

    def __init__(self, parent,  width=120, height=40):
        super().__init__(parent, width=width, height=height)
        sys.stdout = self
        sys.stderr = self
        self.init_events()
        self.init_prompt()
        self.update_input()
        self.interpreter = code.InteractiveInterpreter(sys.modules['__main__'].__dict__)
        self.completer = rl.Completer()

    def init_events(self):
        self.bind('<Return>', self.handle_enter)
        self.bind('<Left>', self.handle_left)
        self.bind('<BackSpace>', self.handle_left)
        self.bind('<Up>', self.handle_up)
        self.bind('<Down>', self.handle_down)
        self.bind('<Tab>', self.handle_tab)

    def init_prompt(self):
        try:
            self.ps1 = sys.ps1
        except AttributeError:
            self.ps1 = ">>> "
        try:
            self.ps2 = sys.ps2
        except AttributeError:
            self.ps2 = "... "

    def get_current_input(self):
        line_index = int(self.index(tk.INSERT).split('.')[0])
        line = self.get(f'{line_index}.{len(self.prompt)}', f'{line_index}.end')
        return line

    def handle_enter(self, *args):
        line = self.get_current_input()
        self.inputBuffer.append(line)
        rl.readline.add_history(line)
        source ='\n'.join(self.inputBuffer)
        self.insert(tk.INSERT, f'\n')
        try:
            more = self.interpreter.runsource(source)
            self.update_input(newCommand = not(more and line))
            return 'break'
        except SyntaxError as e:
            self.update_input(newCommand = not(more and line))
            return 'break'

    def handle_left(self, *args):
        column_index = int(self.index(tk.INSERT).split('.')[1])
        if column_index <= len(self.prompt):
            return 'break'

    def handle_down(self, *args):
        if(self.history_index > 1):
            self.history_index -= 1
            self.select_current_history_item()
        return 'break'

    def handle_up(self, *args):
        if(self.history_index < rl.readline.get_current_history_length()):
            self.history_index += 1
            self.select_current_history_item()
        return 'break'

    def select_current_history_item(self):
        line_index = int(self.index(tk.INSERT).split('.')[0])
        self.mark_set(tk.INSERT, f'{line_index}.{len(self.prompt)}')
        self.delete(tk.INSERT, tk.END)
        self.insert(tk.INSERT, rl.readline.get_history_item(1 + rl.readline.get_current_history_length() - self.history_index))

    def handle_tab(self, *args):
        line =  self.get_current_input()
        terms = line.split(' ')
        completions = []
        for index in range(sys.maxsize):
            completion = self.completer.complete(terms[-1], index)
            if completion is None:
                break
            completions.append(completion)
        if len(completions) == 1:
            self.insert(tk.INSERT, completions[0][len(terms[-1]):-1])
        elif len(completions) > 1:
            completions = '\t'.join(completions)
            self.write(f'\n{completions}\n')
            self.insert(tk.INSERT, f'{self.prompt}{line}')
        return 'break'

    def reset_input_buffer(self):
        self.inputBuffer = []

    def update_input(self, newCommand=True):
        if newCommand:
            self.prompt = self.ps1
            self.reset_input_buffer()
        else:
            self.prompt = self.ps2
        self.insert(tk.INSERT, self.prompt)
        self.history_index = 0

    def write(self, text):
        self.insert(tk.INSERT, text)
        self.mark_set(tk.INSERT, tk.END)

    def flush(self):
        pass

if __name__ == "__main__":
    root = tk.Tk()
    console = Console(root)
    console.pack(fill=tk.BOTH)
    root.mainloop()
